/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:39:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/23 18:32:34 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "map.h"

t_vec2u	sprite_pos(t_map *map, t_sprite *sprite)
{
	t_cell	*cell;
	t_vec2u	pos;

	cell = (t_cell *)((char *)sprite - offsetof(t_cell, sprite));
	pos.x = (cell - map->cells) % map->size.x;
	pos.y = (cell - map->cells) / map->size.x;
	return (pos);
}

void	queue_sprite(t_sprite **lst, t_sprite *sprite)
{
	while (*lst && *lst != sprite && (*lst)->dist > sprite->dist)
		lst = &(*lst)->next;
	if (*lst == sprite)
		return ;
	sprite->next = *lst;
	*lst = sprite;
}
