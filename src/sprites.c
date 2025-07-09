/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:39:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/02 07:48:25 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "map.h"
#include "types.h"

t_vec2f	sprite_pos(t_map *map, t_sprite *sprite)
{
	t_cell	*cell;
	t_vec2f	pos;

	cell = (t_cell *)((char *)sprite - offsetof(t_cell, sprite));
	pos.x = (uint32_t)((cell - map->cells) % map->size.x) + 0.5;
	pos.y = (uint32_t)((cell - map->cells) / map->size.x) + 0.5;
	return (pos);
}

void	queue_sprite(t_sprite **lst, t_sprite *sprite,
			t_map *map, t_vec2f origin)
{
	sprite->rel_pos = vec2f_sub(sprite_pos(map, sprite), origin);
	sprite->dist = hypotf(sprite->rel_pos.x, sprite->rel_pos.y);
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
