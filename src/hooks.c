/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:12:02 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/27 21:43:48 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ft_bitwise.h"

#include "cub3d.h"
#include "defaults.h"
#include "input.h"
#include "types.h"

#define MAXKEYCODE 350

static const t_kb_bit	g_is_pressed[MAXKEYCODE] = {
[MLX_KEY_W] = H_FORWARDS,
[MLX_KEY_A] = H_LEFT,
[MLX_KEY_S] = H_BACKWARDS,
[MLX_KEY_D] = H_RIGHT,
[MLX_KEY_LEFT_SHIFT] = H_SPRINT,
[MLX_KEY_LEFT] = H_LOOKLEFT,
[MLX_KEY_RIGHT] = H_LOOKRIGHT,
};

static const t_kb_bit	g_was_pressed[MAXKEYCODE] = {
[MLX_KEY_ESCAPE] = P_QUIT,
[MLX_KEY_SPACE] = P_PAUSE,
[MLX_KEY_M] = P_MINIMAP,
[MLX_KEY_F3] = P_DEBUG,
[MLX_KEY_F11] = P_FULLSCREEN,
};

void	hook_key(mlx_key_data_t keydata, void *param)
{
	t_kb	*kb;
	bool	down;

	kb = param;
	if (keydata.key < 0 || MAXKEYCODE <= keydata.key)
		return ;
	down = keydata.action != MLX_RELEASE;
	if (g_is_pressed[keydata.key])
		*kb = ft_bit_set_to(*kb, g_is_pressed[keydata.key], down);
	if (keydata.action == MLX_PRESS && g_was_pressed[keydata.key])
		*kb = ft_bit_set(*kb, g_was_pressed[keydata.key]);
}

void	hook_cursor(double xpos, double ypos, void *param)
{
	t_ctx			*ctx;
	t_vec2			pos;
	static double	lastx;

	ctx = param;
	if (ctx->paused)
		return ;
	if (ctx->ignore_mouse)
	{
		mlx_get_mouse_pos(ctx->mlx, &pos.x, &pos.y);
		lastx = pos.x;
		ctx->ignore_mouse--;
	}
	if (xpos == lastx)
		return ;
	vec2f_rotate(&ctx->player.dir, ROT_PER_PX * (xpos - lastx));
	player_set_fov(&ctx->player, 0);
	lastx = xpos;
	(void)ypos;
}
