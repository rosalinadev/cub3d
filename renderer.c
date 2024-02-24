/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:59:35 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/24 19:58:00 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	draw_cell(t_ctx *ctx, t_coords c, t_cell_type t)
{
	unsigned char	frame;

	if (ctx->map->c[c.y][c.x].t == t)
	{
		frame = 0;
		while (frame < 3)
		{
			if (mlx_image_to_window(ctx->mlx, ctx->assets[frame][t].\
				img[ctx->map->c[c.y][c.x].v], c.x * CSIZE, c.y * CSIZE) < 0)
				return (-1);
			ctx->assets[frame][t].img[ctx->map->c[c.y][c.x].v]->enabled =!frame;
			frame++;
		}
	}
	return (0);
}

int	draw_static(t_ctx *ctx)
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
