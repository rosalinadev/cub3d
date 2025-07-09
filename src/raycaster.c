/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:48:59 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/02 07:49:15 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "raycast.h"

static inline void	mirror_ray(t_raycast *ray)
{
	ray->reflected = true;
	if (ray->hit_side == SIDE_W || ray->hit_side == SIDE_E)
	{
		ray->pos.x -= ray->step.x;
		ray->step.x = -ray->step.x;
		ray->flip_ns = !ray->flip_ns;
	}
	else
	{
		ray->pos.y -= ray->step.y;
		ray->step.y = -ray->step.y;
		ray->flip_we = !ray->flip_we;
	}
	ray->hit_cell = get_cell(ray->map, ray->pos);
}

static inline void	dda_hooks(t_raycast *ray)
{
	if (ray->hit_cell->type == C_MIRROR)
		mirror_ray(ray);
	if (!ray->reflected && ray->hit_cell->type == C_SPRITE
		&& !ray->hit_cell->sprite.added)
		queue_sprite(&ray->sprites, &ray->hit_cell->sprite,
			ray->map, ray->player->pos);
}

static inline void	dda(t_raycast *ray)
{
	while (!ray->hit && ray->render_distance--)
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
		if (!ray->interact)
			dda_hooks(ray);
		if ((ray->interact && ray->hit_cell->type == C_DOOR)
			|| collides(ray->hit_cell))
			ray->hit = true;
	}
	ray->dist = ray->side.x - ray->delta.x;
	if (ray->hit_side == SIDE_N || ray->hit_side == SIDE_S)
		ray->dist = ray->side.y - ray->delta.y;
}

// FIXME find root cause of hit_x going negative (WHY?!)
void	cast_ray(t_raycast *ray, uint32_t max_dist)
{
	ray->pos = vec2f_floor(ray->player->pos);
	ray->delta = (t_vec2f){fabsf(1 / ray->dir.x), fabsf(1 / ray->dir.y)};
	ray->step = (t_vec2){1 - 2 * (ray->dir.x < 0), 1 - 2 * (ray->dir.y < 0)};
	ray->side = (t_vec2f){fabsf((ray->dir.x >= 0) - fabsf(ray->pos.x
				- ray->player->pos.x)) * ray->delta.x, fabsf((ray->dir.y >= 0)
			- fabsf(ray->pos.y - ray->player->pos.y)) * ray->delta.y};
	ray->render_distance = max_dist;
	ray->hit = false;
	ray->reflected = false;
	ray->flip_we = false;
	ray->flip_ns = false;
	dda(ray);
	ray->hit_x = ray->player->pos.y + ray->dist * ray->dir.y;
	if (ray->hit_side == SIDE_N || ray->hit_side == SIDE_S)
		ray->hit_x = ray->player->pos.x + ray->dist * ray->dir.x;
	ray->hit_x = modff(ray->hit_x, &ray->hit_x);
	if (ray->hit_x < 0)
		ray->hit_x = 1 + ray->hit_x;
	if ((ray->hit_side == SIDE_W || ray->hit_side == SIDE_S))
		ray->hit_x = 1 - ray->hit_x;
	if ((ray->hit_side == SIDE_W || ray->hit_side == SIDE_E) && ray->flip_we)
		ray->hit_x = 1 - ray->hit_x;
	if ((ray->hit_side == SIDE_N || ray->hit_side == SIDE_S) && ray->flip_ns)
		ray->hit_x = 1 - ray->hit_x;
}
