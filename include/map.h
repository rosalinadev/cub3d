/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 03:56:01 by rvandepu          #+#    #+#             */
/*   Updated: 2025/04/04 09:14:23 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stdbool.h>
# include "types.h"

typedef enum e_cell_type
{
	C_OOB = 0,
	C_EMPTY,
	C_WALL,
	C_DOOR,
	C_SPRITE,
	C_SPAWN,
	C__MAXTYPE
}	t_cell_type;

typedef struct s_cell
{
	t_cell_type	type;
	union
	{
		bool	door_open;
	};
}	t_cell;

// TODO sprites :D
typedef struct s_map
{
	t_vec2u	size;
	t_cell	**cells;
	t_vec2u	spawn_pos;
	t_vec2f	spawn_facing;
	bool	is_bonus;
}	t_map;

// map_loader.c
void			free_map(t_map *map);
bool			load_map(t_map *map, const char *path);

// map_utils.c
inline t_cell	get_cell(t_map *map, t_vec2 pos)
{
	if (pos.x < 0 || pos.y < 0
		|| (uint32_t)pos.x >= map->size.x
		|| (uint32_t)pos.y >= map->size.y)
		return ((t_cell){.type = C_OOB});
	return (map->cells[pos.y][pos.x]);
}

#endif
