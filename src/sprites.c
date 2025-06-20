/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:39:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/21 06:33:02 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
