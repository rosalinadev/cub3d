/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:11:07 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/10 15:37:55 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	alloc_mem(t_map *map, unsigned int depth)
{
	int	*line;

	if (depth == map->height)
	{
		map->mem = ft_calloc(depth, sizeof(int *));
		if (map->mem == NULL)
			g_eno = E_MEM;
		return (map->mem != NULL);
	}
	line = ft_calloc(map->width, sizeof(int));
	if (line == NULL)
		return (g_eno = E_MEM, false);
	if (!alloc_mem(map, depth + 1))
		return (free(line), false);
	return (map->mem[depth] = line, true);
}

void	clear_mem(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->height)
		ft_bzero(map->mem[i++], map->width * sizeof(int));
}

void	free_mem(t_map *map)
{
	unsigned int	i;

	i = 0;
	while (i < map->height)
		free(map->mem[i++]);
	free(map->mem);
	map->mem = NULL;
}

static bool	traverse_map(t_map *map, t_coords c)
{
	static bool	exit_reached = false;

	if (map->mem[c.y][c.x] || map->c[c.y][c.x].t == C_WALL)
		return (true);
	map->mem[c.y][c.x] = true;
	if (map->c[c.y][c.x].t == C_COLLECTIBLE)
		map->collectibles--;
	else if (map->c[c.y][c.x].t == C_EXIT)
		exit_reached = true;
	traverse_map(map, (t_coords){c.x + 1, c.y});
	traverse_map(map, (t_coords){c.x, c.y + 1});
	traverse_map(map, (t_coords){c.x - 1, c.y});
	traverse_map(map, (t_coords){c.x, c.y - 1});
	if (!exit_reached)
		g_eno = E_EXITREACH;
	return (exit_reached);
}

bool	map_is_valid(t_map *map)
{
	unsigned int	o_collectibles;

	if (!map->has_player || !map->collectibles || !map->has_exit)
		return (g_eno = E_MAPCONTENTS, false);
	if (!alloc_mem(map, 0))
		return (false);
	o_collectibles = map->collectibles;
	if (!traverse_map(map, map->player->c))
		return (false);
	if (map->collectibles)
		return (g_eno = E_COLLECTREACH, false);
	map->collectibles = o_collectibles;
	return (true);
}
