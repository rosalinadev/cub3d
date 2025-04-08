/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:39:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/04/08 17:03:13 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "types.h"
#include "map.h"

t_vec2u	sprite_pos(t_map *map, t_sprite *sprite)
{
	t_cell	*cell;
	t_vec2u	pos;

	cell = (t_cell *)((void *)sprite - offsetof(t_cell, sprite));
	pos.x = (cell - map->cells) % map->size.x;
	pos.y = (cell - map->cells) / map->size.x;
	return (pos);
}

/*bool	init_entities(t_map *map, t_coords c, unsigned int depth)
{
	while (c.y != map->height && map->c[c.y][c.x].t != C_PLAYER
									&& map->c[c.y][c.x].t != C_ENEMY)
		if (++c.x == map->width)
			c.x = (c.y++, 0);
	if (c.y == map->height)
	{
		map->entities = ft_calloc(depth, sizeof(t_entity));
		if (map->entities == NULL)
			return (g_eno = E_MEM, false);
		return (map->num_entities = depth, true);
	}
	if (!init_entities(map, (t_coords){(c.x + 1) * (c.x + 1 != map->width),
			c.y + (c.x + 1 == map->width)}, depth + 1))
		return (false);
	if (map->c[c.y][c.x].t == C_PLAYER)
		map->player = &map->entities[depth];
	map->entities[depth] = (t_entity){.oc = c, .c = c, .t = map->c[c.y][c.x].t};
	return (true);
}*/
