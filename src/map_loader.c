/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:49:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/03/28 02:50:17 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	unsigned int	i;

	if (map)
	{
		i = map->height;
		while (i--)
		{
			if (map->r)
				free(map->r[i]);
			if (map->c)
				free(map->c[i]);
		}
		if (map->r)
			free(map->r);
		if (map->c)
			free(map->c);
		if (map->entities)
			free(map->entities);
		if (map->mem)
			free_mem(map);
		free(map);
	}
}

static bool	prevalidate_set_variants(t_map *map)
{
	unsigned int	x;
	unsigned int	y;

	y = map->height;
	while (y--)
	{
		x = map->width;
		while (x--)
		{
			if (map->c[y][x].t == C_WALL)
			{
				if (x + 1 < map->width && map->c[y][x + 1].t == C_WALL)
					map->c[y][x].v = ft_bit_set(map->c[y][x].v, F_WEST);
				if (y > 0 && map->c[y - 1][x].t == C_WALL)
					map->c[y][x].v = ft_bit_set(map->c[y][x].v, F_NORTH);
				if (x > 0 && map->c[y][x - 1].t == C_WALL)
					map->c[y][x].v = ft_bit_set(map->c[y][x].v, F_EAST);
				if (y + 1 < map->height && map->c[y + 1][x].t == C_WALL)
					map->c[y][x].v = ft_bit_set(map->c[y][x].v, F_SOUTH);
			}
			else if (!x || x == map->width - 1 || !y || y == map->height - 1)
				return (g_eno = E_MAPEDGES, false);
		}
	}
	return (true);
}

static const t_cell_type	g_type_table[0xFF] = {\
	['0'] = C_EMPTY, \
	['1'] = C_WALL, \
	['C'] = C_COLLECTIBLE, \
	['E'] = C_EXIT, \
	['P'] = C_PLAYER, \
	['B'] = C_ENEMY, \
};

static int	parse_types(t_map *map, unsigned int depth)
{
	unsigned int	x;
	t_cell			*cells;

	if (depth == map->height)
		return (-((map->c = ft_calloc(map->height, sizeof(char *))) == NULL));
	cells = ft_calloc(map->width, sizeof(t_cell));
	if (cells == NULL)
		return (g_eno = E_MEM, -1);
	x = map->width;
	while (x--)
	{
		cells[x].t = g_type_table[(unsigned char)map->r[depth][x]];
		if (!cells[x].t || (cells[x].t == C_PLAYER && map->has_player) \
							|| (cells[x].t == C_EXIT && map->has_exit))
			return (g_eno = E_MAPCONTENTS, free(cells), -1);
		if (cells[x].t == C_PLAYER)
			map->has_player = true;
		if (cells[x].t == C_COLLECTIBLE)
			map->collectibles++;
		if (cells[x].t == C_EXIT)
			map->has_exit = true;
	}
	if (parse_types(map, depth + 1) < 0)
		return (free(cells), -1);
	return (map->c[depth] = cells, 0);
}

static int	read_map(t_map *map, int fd, int depth)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
	{
		map->r = ft_calloc(depth, sizeof(char *));
		if (map->r == NULL)
			return (g_eno = E_MEM, -1);
		return (map->height = depth, 0);
	}
	if (depth == 0)
		map->width = ft_strlen(line) - 1;
	else if (ft_strlen(line) - 1 != map->width)
		return (g_eno = E_MAPWIDTH, free(line), -1);
	if (read_map(map, fd, depth + 1) < 0)
		return (free(line), -1);
	return (map->r[depth] = line, 0);
}

int	load_map(t_ctx *ctx)
{
	int		fd;

	fd = open(ctx->path, O_RDONLY);
	if (fd < 0)
		return (g_eno = E_OPEN, -1);
	ctx->map = ft_calloc(1, sizeof(t_map));
	if (ctx->map == NULL)
		return (g_eno = E_MEM, close(fd), -1);
	if (read_map(ctx->map, fd, 0) < 0)
		return (free(ctx->map), close(fd), -1);
	close(fd);
	if (!ctx->map->width || !ctx->map->height)
		return (g_eno = E_MAPEMPTY, free_map(ctx->map), -1);
	if (parse_types(ctx->map, 0) < 0)
		return (free_map(ctx->map), -1);
	if (!prevalidate_set_variants(ctx->map))
		return (free_map(ctx->map), -1);
	if (!init_entities(ctx->map, (t_coords){0, 0}, 0))
		return (free_map(ctx->map), -1);
	if (!map_is_valid(ctx->map))
		return (free_map(ctx->map), -1);
	return (0);
}
