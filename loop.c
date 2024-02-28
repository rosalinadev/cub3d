/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:10:25 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/28 08:16:23 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define FRAME_TIME 0.160
#define MOVE_TIME 0.100

static void	set_frame(t_asset *asset, bool enabled)
{
	unsigned char	variant;

	variant = -1;
	while (++variant < 32)
	{
		if ((asset->is_entity && asset->has_variants && variant % 8 >= 4) \
		|| (asset->is_entity && !asset->has_variants && variant % 8 >= 1) \
		|| (!asset->is_entity && asset->has_variants && variant >= 16) \
		|| (!asset->is_entity && !asset->has_variants && variant >= 1))
			continue ;
		if (asset->img[variant])
			asset->img[variant]->enabled = enabled;
	}
}

static void	update_frame(t_ctx *ctx, double time)
{
	static double			last_time = 0;
	static unsigned char	frame = 0;
	unsigned char			i;
	unsigned char			j;

	if (!last_time)
		return ((void)(last_time = time));
	if (time - last_time < FRAME_TIME)
		return ;
	if (++frame == 3)
		frame = 0;
	i = 0;
	while (++i < C_MAXTYPE)
	{
		j = 3;
		while (j--)
			set_frame(&ctx->assets[j][i], j == frame);
	}
	last_time = time;
}

// TODO
void	ft_hook_loop(void *param)
{
	t_ctx			*ctx;
	static double	last_move_time;

	ctx = param;
	update_frame(ctx, mlx_get_time());
	if ((ft_bit_check(ctx->flags, P_LEFT) || ft_bit_check(ctx->flags, P_RIGHT) \
		|| ft_bit_check(ctx->flags, P_UP) || ft_bit_check(ctx->flags, P_DOWN)) \
	|| ((ft_bit_check(ctx->flags, H_LEFT) || ft_bit_check(ctx->flags, H_RIGHT) \
		|| ft_bit_check(ctx->flags, H_UP) || ft_bit_check(ctx->flags, H_DOWN)) \
		&& mlx_get_time() - last_move_time >= MOVE_TIME))
	{
		clear_mem(ctx->map);
		move_entities();
		(ft_bit_clear(ctx->flags, P_LEFT), ft_bit_clear(ctx->flags, P_RIGHT),
			ft_bit_clear(ctx->flags, P_UP), ft_bit_clear(ctx->flags, P_DOWN));
		last_move_time = mlx_get_time();
	}
	if (ft_bit_check(ctx->flags, P_QUIT))
		mlx_close_window(ctx->mlx);
}
