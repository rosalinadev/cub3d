/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:03:51 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/17 07:23:29 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_cell	*get_cell(t_map *map, t_vec2 pos)
{
	static const t_cell	g_oob = {.type = C_OOB};

	if (pos.x < 0 || map->size.x <= (uint32_t)pos.x
		|| pos.y < 0 || map->size.y <= (uint32_t)pos.y)
		return ((t_cell *)&g_oob);
	return (&map->cells[pos.y * map->size.x + pos.x]);
}
