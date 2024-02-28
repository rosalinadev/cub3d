/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:12:02 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/28 06:35:40 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static const unsigned char	g_is_pressed[350] = {\
	[MLX_KEY_W] = H_UP, \
	[MLX_KEY_A] = H_LEFT, \
	[MLX_KEY_S] = H_DOWN, \
	[MLX_KEY_D] = H_RIGHT, \
};

static const unsigned char	g_was_pressed[350] = {\
	[MLX_KEY_W] = P_UP, \
	[MLX_KEY_A] = P_LEFT, \
	[MLX_KEY_S] = P_DOWN, \
	[MLX_KEY_D] = P_RIGHT, \
	[MLX_KEY_ESCAPE] = P_QUIT, \
};

void	ft_hook_key(mlx_key_data_t keydata, void *param)
{
	t_ctx	*ctx;
	bool	down;

	ctx = param;
	if (keydata.key >= 350)
		return ;
	down = keydata.action != MLX_RELEASE;
	if (g_is_pressed[keydata.key])
		ctx->flags = ft_bit_set_to(ctx->flags, g_is_pressed[keydata.key], down);
	if (keydata.action == MLX_PRESS && g_was_pressed[keydata.key])
		ctx->flags = ft_bit_set(ctx->flags, g_was_pressed[keydata.key]);
}
