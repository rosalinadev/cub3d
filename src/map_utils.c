/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:03:51 by rvandepu          #+#    #+#             */
/*   Updated: 2025/04/08 19:21:34 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_cell	*get_cell(t_map *map, t_vec2 pos)
{
	static const t_cell	g_oob = {.type = C_OOB};

	if (pos.x < 0 || pos.y < 0
		|| (uint32_t)pos.x >= map->size.x
		|| (uint32_t)pos.y >= map->size.y)
		return ((t_cell *)&g_oob);
	return (&map->cells[pos.y * map->size.x + pos.x]);
}
