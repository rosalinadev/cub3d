/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:39:28 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/27 13:58:54 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_entities(t_map *map, t_coords c, unsigned int depth)
{
	while (c.y != map->height && map->c[c.y][c.x].t != C_PLAYER
									&& map->c[c.y][c.x].t != C_ENEMY)
		if (++c.x == map->width)
			c.x = (c.y++, 0);
	if (c.y == map->height)
		return (map->num_entities = depth,
			map->entities = ft_calloc(depth, sizeof(t_entity)), true);
	if (!init_entities(map, (t_coords){(c.x + 1) * (c.x + 1 != map->width),
			c.y + (c.x + 1 == map->width)}, depth + 1))
		return (false);
	if (map->c[c.y][c.x].t == C_PLAYER)
		map->player = &map->entities[depth];
	map->entities[depth] = (t_entity){.c = c, .t = map->c[c.y][c.x].t};
	return (true);
}
