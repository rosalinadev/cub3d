/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:11:07 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/27 08:03:50 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	alloc_mem(t_map *map, unsigned int depth)
{
	bool	*line;

	if (depth == map->height)
		return (map->mem = ft_calloc(depth, sizeof(bool *)), map->mem);
	line = ft_calloc(map->width, sizeof(bool));
	if (line == NULL)
		return (false);
	if (!alloc_mem(map, depth + 1))
		return (free(line), false);
	return (map->mem[depth] = line, true);
}

static bool	free_mem(t_map *map, unsigned int depth)
{
	if (depth == map->height)
		return (false);
	free_mem(map, depth + 1);
	free(map->mem[depth]);
	if (!depth)
		free(map->mem);
	return (false);
}

static bool	traverse_map(t_map *map, t_coords c)
{
	static bool	exit_reached = false;

	if (map->mem[c.y][c.x] || map->c[c.y][c.x].t == C_WALL)
		return (false);
	map->mem[c.y][c.x] = true;
	if (map->c[c.y][c.x].t == C_COLLECTIBLE)
		map->collectibles--;
	else if (map->c[c.y][c.x].t == C_EXIT)
		exit_reached = true;
	traverse_map(map, (t_coords){c.x + 1, c.y});
	traverse_map(map, (t_coords){c.x, c.y + 1});
	traverse_map(map, (t_coords){c.x - 1, c.y});
	traverse_map(map, (t_coords){c.x, c.y - 1});
	return (exit_reached);
}

bool	map_is_valid(t_map *map)
{
	unsigned int	mem;

	if (!map->has_player || !map->collectibles || !map->has_exit)
		return (false);
	if (!alloc_mem(map, 0))
		return (false);
	mem = map->collectibles;
	if (!traverse_map(map, map->player->c))
		return (free_mem(map, 0), false);
	free_mem(map, 0);
	if (map->collectibles)
		return (false);
	map->collectibles = mem;
	return (true);
}
