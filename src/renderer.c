/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:26:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/29 21:42:28 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include "MLX42/MLX42.h"
#include "libft.h"

#include "cub3d.h"
#include "defaults.h"
#include "mlx_utils.h"
#include "raycast.h"

static void	draw_slice(t_ctx *ctx, mlx_texture_t *tex,
		uint32_t x, int32_t height)
{
	int32_t	start;
	int32_t	end;
	t_vec2u	tex_pos;
	t_vec2f	step_pos;

	start = ft_max(2, ((int32_t)ctx->disp->height - height) / 2, 0);
	end = ft_min(2, (ctx->disp->height + height) / 2 + 1, ctx->disp->height);
	tex_pos.x = ctx->ray.hit_x * tex->width;
	if (tex_pos.x >= tex->width)
		tex_pos.x = tex->width - 1;
	step_pos.x = (float)tex->height / height;
	step_pos.y = ceilf(start + ((float)height
				- ctx->disp->height) / 2) * step_pos.x;
	while (start < end)
	{
		tex_pos.y = step_pos.y;
		if (tex_pos.y >= tex->height)
			tex_pos.y = tex->height - 1;
		step_pos.y += step_pos.x;
		((uint32_t *)ctx->disp->pixels)[ctx->disp->width * start++ + x]
			= ((uint32_t *)tex->pixels)[tex->height * tex_pos.x + tex_pos.y];
	}
}

//static void	render_sprites(t_ctx *ctx);

void	render_screen(t_ctx *ctx)
{
	uint32_t	x;
	int			height;

	mlx_clear_image(ctx->disp);
	unlink_sprites(&ctx->ray.sprites);
	ctx->ray = (t_raycast){.map = &ctx->map, .player = &ctx->player};
	x = 0;
	while (x < ctx->disp->width)
	{
		ctx->ray.dir = vec2f_add(ctx->player.dir, vec2f_scale(
					&ctx->player.cam, 2.0 * x / ctx->disp->width - 1));
		cast_ray(&ctx->ray, RENDER_DISTANCE);
		if (ctx->ray.hit)
		{
			height = ctx->disp->width / ctx->ray.dist / ctx->player.cam_len;
			if (ctx->ray.hit_cell->type == C_DOOR)
				draw_slice(ctx, ctx->assets.tex[A_DOOR], x, height);
			else
				draw_slice(ctx, ctx->assets.tex[ctx->ray.hit_side], x, height);
		}
		x++;
	}
	// TODO render sprite queue
}
