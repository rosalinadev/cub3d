/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:39:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/28 20:54:41 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "map.h"
#include "types.h"

t_vec2u	sprite_pos(t_map *map, t_sprite *sprite)
{
	t_cell	*cell;
	t_vec2u	pos;

	cell = (t_cell *)((char *)sprite - offsetof(t_cell, sprite));
	pos.x = (cell - map->cells) % map->size.x;
	pos.y = (cell - map->cells) / map->size.x;
	return (pos);
}

void	queue_sprite(t_sprite **lst, t_sprite *sprite, t_vec2f rel_pos)
{
	sprite->dist = hypotf(rel_pos.x, rel_pos.y);
	while (*lst && *lst != sprite && (*lst)->dist > sprite->dist)
		lst = &(*lst)->next;
	sprite->next = *lst;
	*lst = sprite;
	sprite->added = true;
}

void	unlink_sprites(t_sprite **sprite)
{
	t_sprite	**next;

	while (*sprite)
	{
		next = &(*sprite)->next;
		(*sprite)->added = false;
		*sprite = NULL;
		sprite = next;
	}
}
