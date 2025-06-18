/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:49:01 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/18 15:09:04 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "map.h"
# include "player.h"
# include "types.h"

typedef enum e_side
{
	SIDE_W = 0,
	SIDE_E,
	SIDE_N,
	SIDE_S
}	t_side;

typedef struct s_raycast
{
	t_map		*map;
	t_player	*player;
	t_vec2f		dir;
	t_vec2		pos;
	t_vec2		step;
	t_vec2f		side;
	t_vec2f		delta;
	float		dist;
	bool		hit;
	t_cell		*hit_cell;
	t_side		hit_side;
}	t_raycast;

// raycaster.c
void	cast_ray(t_raycast *ray);

#endif
