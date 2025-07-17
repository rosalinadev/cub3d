/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:26:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/17 22:54:34 by rvandepu         ###   ########.fr       */
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
#include "render.h"
#include "types.h"

static void	draw_slice(t_draw *d)
{
	float		step;
	float		pos;
	int32_t		y;
	uint32_t	*px;
	uint32_t	v;

	if (d->h < d->hbuf[d->x])
		return ;
	d->hbuf[d->x] = d->h;
	step = (float)d->tex->height / d->h;
	pos = ceilf(d->start + ((float)d->h
				- d->disp->height) / 2) * step;
	y = d->start;
	while (y <= d->end)
	{
		d->pos.y = pos;
		if (d->pos.y >= d->tex->height)
			d->pos.y = d->tex->height - 1;
		pos += step;
		px = &((uint32_t *)d->disp->pixels)[d->disp->width * y++ + d->x];
		v = ((uint32_t *)d->tex->pixels)[d->tex->height * d->pos.x + d->pos.y];
		set_pixel((t_col *)px, (t_col){.col = v});
	}
}

static void	render_slice(t_draw *d, mlx_texture_t *tex, t_raycast *ray)
{
	d->tex = tex;
	d->start = ft_max(2, (int32_t)(d->disp->height - d->h) / 2, 0);
	d->end = ft_min(2, (d->disp->height + d->h) / 2, d->disp->height - 1);
	d->pos.x = ray->hit_x * tex->width;
	if (d->pos.x >= tex->width)
		d->pos.x = tex->width - 1;
	draw_slice(d);
}

static void	render_sprite(t_draw *d, t_player *plr, t_vec2f trans)
{
	int32_t	sprite_x;
	int32_t	draw_start;
	int32_t	draw_end;

	sprite_x = (int32_t)(d->disp->width / 2) * (1 + trans.x / trans.y);
	d->h = d->disp->width / trans.y / plr->cam_len;
	d->start = ft_max(2, (int32_t)(d->disp->height - d->h) / 2, 0);
	d->end = ft_min(2, (d->disp->height + d->h) / 2, d->disp->height - 1);
	draw_start = -(int32_t)d->h / 2 + sprite_x;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (int32_t)d->h / 2 + sprite_x;
	if (draw_end > (int32_t)d->disp->width)
		draw_end = d->disp->width;
	while (draw_start < draw_end)
	{
		d->x = draw_start++;
		d->pos.x = (int32_t)((d->x - (-(int32_t)d->h / 2 + sprite_x))
				* d->tex->width / (int32_t)d->h);
		draw_slice(d);
	}
}

static void	render_sprites(t_draw *d, t_player *plr, t_sprite *s)
{
	float	det;
	t_vec2f	trans;
	double	time;

	while (s)
	{
		det = 1.0 / (plr->cam.x * plr->dir.y - plr->dir.x * plr->cam.y);
		trans.x = det * (plr->dir.y * s->rel_pos.x - plr->dir.x * s->rel_pos.y);
		trans.y = det * (plr->cam.x * s->rel_pos.y - plr->cam.y * s->rel_pos.x);
		if (trans.y > 0)
		{
			time = get_time();
			if (time >= s->last_frame + 0.05)
			{
				s->frame = &(*s->frame)->next;
				s->last_frame = time;
			}
			d->tex = (*s->frame)->tex;
			render_sprite(d, plr, trans);
		}
		s = s->next;
	}
}

void	render_screen(t_ctx *ctx)
{
	t_draw	draw;

	draw_background(ctx->disp, ctx->assets.ceil, ctx->assets.floor);
	unlink_sprites(&ctx->ray.sprites);
	ctx->ray = (t_raycast){.map = &ctx->map, .player = &ctx->player};
	draw = (t_draw){.disp = ctx->disp, .hbuf = ctx->hbuf};
	ft_bzero(draw.hbuf, sizeof(*draw.hbuf) * ctx->size.x);
	while (draw.x < ctx->disp->width)
	{
		ctx->ray.dir = vec2f_add(ctx->player.dir, vec2f_scale(
					&ctx->player.cam, 2.0 * draw.x / ctx->disp->width - 1));
		cast_ray(&ctx->ray, RENDER_DISTANCE);
		if (ctx->ray.hit)
		{
			draw.h = ctx->disp->width / ctx->ray.dist / ctx->player.cam_len;
			if (ctx->ray.hit_cell->type == C_DOOR)
				render_slice(&draw, ctx->assets.tex[A_DOOR], &ctx->ray);
			else
				render_slice(&draw,
					ctx->assets.tex[ctx->ray.hit_side], &ctx->ray);
		}
		draw.x++;
	}
	render_sprites(&draw, &ctx->player, ctx->ray.sprites);
}
