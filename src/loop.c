/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:10:25 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/28 00:48:16 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitwise.h"

#include "cub3d.h"
#include "defaults.h"
#include "mlx_utils.h"
#include "raycast.h"
#include "types.h"

static inline void	try_move(t_map *map, t_player *plr, t_vec2f np)
{
	if (plr->noclip)
	{
		plr->pos = np;
		return ;
	}
	if (!collides(get_cell(map, vec2f_floor((t_vec2f){np.x, plr->pos.y}))))
	{
		plr->pos.x = np.x;
		if (!collides(get_cell(map, vec2f_floor(np))))
			plr->pos = np;
	}
	else if (!collides(get_cell(map, vec2f_floor((t_vec2f){plr->pos.x, np.y}))))
	{
		plr->pos.y = np.y;
		if (!collides(get_cell(map, vec2f_floor(np))))
			plr->pos = np;
	}
}

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
	mov_scaled = vec2f_scale(&ctx->player.dir, MOV_SPEED * delta
			* (1 + SPRINT_BOOST * ft_bit_check(ctx->kb, H_SPRINT)));
	if (ft_bit_check(ctx->kb, H_FORWARDS))
		newpos = vec2f_add(newpos, mov_scaled);
	if (ft_bit_check(ctx->kb, H_BACKWARDS))
		newpos = vec2f_sub(newpos, mov_scaled);
	if (ft_bit_check(ctx->kb, H_LEFT))
		newpos = vec2f_add(newpos, ((t_vec2f){mov_scaled.y, -mov_scaled.x}));
	if (ft_bit_check(ctx->kb, H_RIGHT))
		newpos = vec2f_add(newpos, ((t_vec2f){-mov_scaled.y, mov_scaled.x}));
	try_move(&ctx->map, &ctx->player, newpos);
}

#define INTERACT_RANGE 2

static void	interact(t_map *map, t_player *player)
{
	t_raycast	ray;

	ray = (t_raycast){.map = map, .player = player,
		.dir = player->dir, .interact = true};
	cast_ray(&ray, INTERACT_RANGE);
	if (!ray.hit)
		return ;
	if (ray.hit_cell->type == C_DOOR)
		ray.hit_cell->door_open ^= true;
}

// how many cursor hook calls to ignore after pausing/unpausing
// minimum 1 to reset last position in hook
#define MOUSE_IGNORE_CALLS 3

static void	handle_input(t_ctx *ctx)
{
	if (ft_bit_check(ctx->kb, P_PAUSE))
	{
		ctx->paused = !ctx->paused;
		ctx->text->enabled = ctx->paused;
		if (ctx->paused)
			mlx_set_cursor_mode(ctx->mlx, MLX_MOUSE_NORMAL);
		else
			mlx_set_cursor_mode(ctx->mlx, MLX_MOUSE_DISABLED);
		ctx->ignore_mouse = MOUSE_IGNORE_CALLS;
		ctx->kb = ft_bit_clear(ctx->kb, P_PAUSE);
	}
	if (ctx->debug && ft_bit_check(ctx->kb, P_NOCLIP))
		ctx->player.noclip ^= true;
	ctx->kb = ft_bit_clear(ctx->kb, P_NOCLIP);
	if (ft_bit_check(ctx->kb, P_INTERACT))
		interact(&ctx->map, &ctx->player);
	ctx->kb = ft_bit_clear(ctx->kb, P_INTERACT);
}

void	hook_loop(void *param)
{
	t_ctx			*ctx;
	static double	last_input = -1;
	static double	last_frame = -1;
	double			time;

	ctx = param;
	time = get_time();
	if (time - last_input >= 0.001)
	{
		if (!ctx->paused)
			handle_movement(ctx, time - last_input);
		last_input = time;
		handle_input(ctx);
	}
	if (time - last_frame >= 1.0 / FPS)
	{
		time = get_time();
		last_frame = time;
		render_screen(ctx);
		draw_debug(ctx, get_time() - time);
	}
	if (ft_bit_check(ctx->kb, P_QUIT) || ft_bit_check(ctx->kb, P_FULLSCREEN))
		mlx_close_window(ctx->mlx);
}
