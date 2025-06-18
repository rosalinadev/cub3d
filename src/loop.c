/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:10:25 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/18 15:06:03 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitwise.h"

#include "cub3d.h"
#include "defaults.h"

/*static inline void	draw_movecount(t_ctx *ctx)
{
	static unsigned int	old_movecount;
	t_coords			c;
	char				str[23];
	char				b[11];

	if (ctx->map->movecount != old_movecount)
	{
		ft_bzero(ctx->counter->pixels,
			ctx->counter->width * ctx->counter->height * 4);
		ft_bzero(str, 23);
		ft_strlcat(str, "Move count: ", 23);
		putnbr_buf(ctx->map->movecount, b);
		ft_strlcat(str, b, 23);
		c = str_size(&ctx->font, str);
		if (c.x < ctx->counter->width && c.y < ctx->counter->height)
			draw_str(ctx->counter, &ctx->font, str, (t_coords)
			{ctx->counter->width - 1 - c.x, ctx->counter->height - 1 - c.y});
		ft_printf("%s\n", str);
		old_movecount = ctx->map->movecount;
	}
}*/

// FIXME handle movement along each axis independently to stop getting stuck
static void	handle_movement(t_ctx *ctx, double delta)
{
	t_vec2f			newpos;
	t_vec2f			mov_scaled;

	if (ctx->kb & 0b11 << H_LOOKLEFT)
	{
		if (ft_bit_check(ctx->kb, H_LOOKLEFT))
			vec2f_rotate(&ctx->player.dir, -ROT_SPEED * delta);
		if (ft_bit_check(ctx->kb, H_LOOKRIGHT))
			vec2f_rotate(&ctx->player.dir, +ROT_SPEED * delta);
		player_set_fov(&ctx->player, 0);
	}
	if (!(ctx->kb & 0b1111 << H_FORWARDS))
		return ;
	newpos = ctx->player.pos;
	mov_scaled = vec2f_scale(&ctx->player.dir, MOV_SPEED * delta);
	if (ft_bit_check(ctx->kb, H_FORWARDS))
		newpos = vec2f_add(newpos, mov_scaled);
	if (ft_bit_check(ctx->kb, H_BACKWARDS))
		newpos = vec2f_sub(newpos, mov_scaled);
	if (ft_bit_check(ctx->kb, H_LEFT))
		newpos = vec2f_add(newpos, ((t_vec2f){mov_scaled.y, -mov_scaled.x}));
	if (ft_bit_check(ctx->kb, H_RIGHT))
		newpos = vec2f_add(newpos, ((t_vec2f){-mov_scaled.y, mov_scaled.x}));
	if (!collides(get_cell(&ctx->map, vec2f_floor(newpos))))
		ctx->player.pos = newpos;
}

bool	render_screen(mlx_image_t *img, t_map *map, t_player *player);
void	draw_debug(t_ctx *ctx);

static inline void	tick(t_ctx *ctx)
{
	static double	last_move = -1;
	static double	last_frame = -1;
	double			time;

	time = mlx_get_time();
	if (time - last_move >= 0.001)
	{
		handle_movement(ctx, time - last_move);
		last_move = time;
	}
	if (time - last_frame >= 0.01)
	{
		last_frame = time;
		render_screen(ctx->disp, &ctx->map, &ctx->player);
		draw_debug(ctx);
	}
}

// if only the subject allowed usleep to avoid killing a CPU core
void	hook_loop(void *param)
{
	t_ctx			*c;
	//static double	last_move_time;

	c = param;
	/*update_frame(c, mlx_get_time());
	flags = interpret_input(&c->flags);
	if (ft_bit_check(flags, P_PAUSE) && c->map->gamestate <= G_PAUSED)
		c->map->gamestate = (c->flags &= ~(1 << P_PAUSE), !c->map->gamestate);
	if (c->map->gamestate == G_PLAYING && (flags & 0b1111 << P_UP || (flags \
			& 0b1111 << H_UP && mlx_get_time() - last_move_time >= MOVE_TIME)))
	{
		clear_mem(c->map);
		set_map_weights(c->map, c->map->player->c, 1);
		if (move_player(c, flags))
			c->map->movecount++;
		move_enemies(c);
		iter_entities_variant(c, update_entity_variant);
		last_move_time = mlx_get_time();
	}
	render_entities(c, mlx_get_time());
	draw_movecount(c);*/
	tick(c);
	if (ft_bit_check(c->kb, P_QUIT))
		mlx_close_window(c->mlx);
}
