/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:48:59 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/19 08:13:32 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "defaults.h"
#include "raycast.h"

// TODO figure out which variable to step back when textures are involved
static inline void	mirror_ray(t_raycast *ray)
{
	if (ray->hit_side == SIDE_W || ray->hit_side == SIDE_E)
	{
		//ray->side.x -= ray->delta.x;
		ray->pos.x -= ray->step.x;
		ray->step.x = -ray->step.x;
	}
	else
	{
		//ray->side.y -= ray->delta.y;
		ray->pos.y -= ray->step.y;
		ray->step.y = -ray->step.y;
	}
	ray->hit_cell = get_cell(ray->map, ray->pos);
}

static inline void	dda_hooks(t_raycast *ray)
{
	if (ray->hit_cell->type == C_MIRROR)
		mirror_ray(ray);
}

static inline void	dda(t_raycast *ray)
{
	int	i;

	i = RENDER_DISTANCE;
	while (!ray->hit && i--)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->pos.x += ray->step.x;
			ray->hit_side = ray->step.x == 1;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->pos.y += ray->step.y;
			ray->hit_side = 2 + (ray->step.y == 1);
		}
		ray->hit_cell = get_cell(ray->map, ray->pos);
		dda_hooks(ray);
		if (collides(ray->hit_cell))
			ray->hit = true;
	}
	ray->dist = ray->side.x - ray->delta.x;
	if (ray->hit_side == SIDE_N || ray->hit_side == SIDE_S)
		ray->dist = ray->side.y - ray->delta.y;
}

void	cast_ray(t_raycast *ray)
{
	ray->pos = vec2f_floor(ray->player->pos);
	ray->delta = (t_vec2f){fabsf(1 / ray->dir.x), fabsf(1 / ray->dir.y)};
	ray->step = (t_vec2){1 - 2 * (ray->dir.x < 0), 1 - 2 * (ray->dir.y < 0)};
	ray->side = (t_vec2f){fabsf((ray->dir.x >= 0) - fabsf(ray->pos.x
				- ray->player->pos.x)) * ray->delta.x, fabsf((ray->dir.y >= 0)
			- fabsf(ray->pos.y - ray->player->pos.y)) * ray->delta.y};
	ray->hit = false;
	dda(ray);
}
