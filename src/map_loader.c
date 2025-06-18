/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:49:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/18 04:02:09 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

#include "error.h"
#include "map.h"

#define MAP_CHARS       " 01NSEW"
#define MAP_CHARS_BONUS " 01DXNSEW"

static const t_cell_type	g_type_map[0x100] = {
[' '] = C_OOB,
['0'] = C_EMPTY,
['1'] = C_WALL,
['D'] = C_DOOR,
['X'] = C_SPRITE,
['N'] = C_SPAWN,
['S'] = C_SPAWN,
['E'] = C_SPAWN,
['W'] = C_SPAWN,
};

// these shouldn't be scaled
static const t_vec2f		g_facing_map[0x100] = {\
['N'] = {0, -1},
['S'] = {0, 1},
['E'] = {1, 0},
['W'] = {-1, 0},
};

static bool	parse_line_pre_alloc(t_map *map, char *line)
{
	char	*s;

	s = ft_strrchr(line, '\n');
	if (s)
		*s = '\0';
	s = MAP_CHARS;
	if (map->is_bonus)
		s = MAP_CHARS_BONUS;
	if (ft_strspn(line, s) != ft_strlen(line))
		return (eno(E_MAP_CHARS), false);
	return (true);
}

static bool	parse_line(t_map *map, const char *line, t_vec2u pos, bool final)
{
	static bool	has_spawnpoint;
	t_cell		*cell;

	while (line[pos.x])
	{
		cell = get_cell(map, vec2_u2s(pos));
		cell->type = g_type_map[(uint8_t)line[pos.x]];
		if (cell->type == C_SPAWN)
		{
			if (has_spawnpoint)
				return (eno(E_MAP_SPAWNS), false);
			map->spawn_pos = pos;
			map->spawn_facing = g_facing_map[(uint8_t)line[pos.x]];
			has_spawnpoint = true;
		}
		pos.x++;
	}
	if (final && !has_spawnpoint)
		return (eno(E_MAP_SPAWN), false);
	return (true);
}

static bool	read_map(t_map *map, int fd, int depth)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		if (depth == 0 || map->size.x == 0)
			return (eno(E_MAP_EMPTY), false);
		map->cells = ft_calloc(map->size.x * depth, sizeof(t_cell));
		if (map->cells == NULL)
			return (eno(E_MEM), free(map->cells), false);
		return (map->size.y = depth, true);
	}
	if (!parse_line_pre_alloc(map, line))
		return (free(line), false);
	map->size.x = ft_max(2, map->size.x, ft_strlen(line));
	if (!read_map(map, fd, depth + 1))
		return (free(line), false);
	if (!parse_line(map, line, (t_vec2u){0, depth}, depth == 0))
		return (free(line), false);
	return (free(line), true);
}

static bool	is_enclosed(t_map *map, t_vec2 pos, bool *mem)
{
	static bool	enclosed = true;
	t_cell_type	type;

	if (!enclosed)
		return (false);
	type = get_cell(map, pos)->type;
	if (type == C_OOB)
		return (enclosed = false);
	if (type == C_WALL || mem[pos.y * map->size.x + pos.x])
		return (true);
	mem[pos.y * map->size.x + pos.x] = true;
	is_enclosed(map, (t_vec2){pos.x + 1, pos.y}, mem);
	is_enclosed(map, (t_vec2){pos.x, pos.y + 1}, mem);
	is_enclosed(map, (t_vec2){pos.x - 1, pos.y}, mem);
	is_enclosed(map, (t_vec2){pos.x, pos.y - 1}, mem);
	return (enclosed);
}

bool	load_map(t_map *map, const char *path)
{
	int		fd;
	bool	*mem;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (eno(E_OPEN), false);
	// TODO parse map metadata
	if (!read_map(map, fd, 0))
		return (close(fd), free_gnl(), false);
	close(fd);
	mem = ft_calloc(map->size.x * map->size.y, sizeof(*mem));
	if (mem == NULL)
		return (eno(E_MEM), free(map->cells), false);
	if (!is_enclosed(map, (t_vec2){map->spawn_pos.x, map->spawn_pos.y}, mem))
		return (eno(E_MAP_WALLS), free(mem), free(map->cells), false);
	free(mem);
	return (true);
}
