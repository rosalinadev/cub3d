/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:59:35 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/01 22:30:43 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	draw_cell(t_ctx *ctx, t_coords c, t_cell_type t)
{
	unsigned char	frame;
	t_cell			*cell;

	cell = &ctx->map->c[c.y][c.x];
	if (cell->t == t)
	{
		frame = 0;
		while (frame < 3)
		{
			cell->i[frame] = mlx_image_to_window(ctx->mlx, \
				ctx->assets[frame][t].img[cell->v], c.x * CSIZE, c.y * CSIZE);
			if (cell->i[frame] < 0)
				return (-1);
			ctx->assets[frame][t].img[cell->v]->enabled =!frame;
			frame++;
		}
	}
	return (0);
}

int	draw_map(t_ctx *ctx)
{
	t_coords		c;

	c.y = ctx->map->height;
	while (c.y--)
	{
		c.x = ctx->map->width;
		while (c.x--)
		{
			if (draw_cell(ctx, c, C_WALL) < 0 \
			|| draw_cell(ctx, c, C_COLLECTIBLE) < 0 \
			|| draw_cell(ctx, c, C_EXIT) < 0)
				return (-1);
		}
	}
	return (0);
}

int	draw_entity_variant(t_ctx *ctx, t_entity *entity, unsigned int variant)
{
	unsigned char	frame;

	frame = 0;
	while (frame < 3)
	{
		entity->i[frame][variant] = mlx_image_to_window(ctx->mlx, \
			ctx->assets[frame][entity->t].img[variant], \
			entity->c.x * CSIZE, entity->c.y * CSIZE);
		if (entity->i[frame][variant] < 0)
			return (-1);
		ctx->assets[frame][entity->t].img[variant]->enabled =!frame;
		ctx->assets[frame][entity->t].img[variant] \
			->instances[entity->i[frame][variant]].enabled = !variant;
		frame++;
	}
	return (0);
}

int	update_entity_variant(t_ctx *ctx, t_entity *entity, unsigned int variant)
{
	unsigned char	frame;

	if ((entity->oc.x != entity->c.x || entity->oc.y != entity->c.y) && \
		ctx->assets[0][entity->t].has_variants && !variant && ++entity->f == 4)
		entity->f = 0;
	frame = -1;
	while (++frame < 3)
		ctx->assets[frame][entity->t].img[variant]->instances[entity->i[frame] \
			[variant]].enabled = entity->d * 8 + entity->f == variant;
	return (0);
}

void	render_entities(t_ctx *ctx, double start, double curr)
{
	unsigned int	i;
	unsigned int	f;
	unsigned char	v;
	t_entity		*e;

	if (curr - start > MOVE_TIME)
		curr = start + MOVE_TIME;
	i = -1;
	while (++i < ctx->map->num_entities)
	{
		e = &ctx->map->entities[i];
		v = e->d * 8 + e->f;
		f = -1;
		while (++f < 3)
		{
			ctx->assets[f][e->t].img[v]->instances[e->i[f][v]].x = round(CSIZE \
			* (e->oc.x + (curr - start) / MOVE_TIME * (int)(e->c.x - e->oc.x)));
			ctx->assets[f][e->t].img[v]->instances[e->i[f][v]].y = round(CSIZE \
			* (e->oc.y + (curr - start) / MOVE_TIME * (int)(e->c.y - e->oc.y)));
		}
	}
}
