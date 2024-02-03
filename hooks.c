/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:12:02 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/03 19:58:00 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static const unsigned char	g_is_pressed[350] = {\
	[MLX_KEY_W] = F_UP, \
	[MLX_KEY_A] = F_LEFT, \
	[MLX_KEY_S] = F_DOWN, \
	[MLX_KEY_D] = F_RIGHT, \
};

static const unsigned char	g_was_pressed[350] = {\
	[MLX_KEY_ESCAPE] = F_QUIT, \
};

void	ft_hook_key(mlx_key_data_t keydata, void *param)
{
	t_ctx	*ctx;
	bool	b;

	ctx = param;
	if (keydata.key >= 350)
		return ;
	b = keydata.action != MLX_RELEASE;
	if (g_is_pressed[keydata.key])
		ctx->flags = ft_bit_set_to(ctx->flags, g_is_pressed[keydata.key], b);
	else if (b && g_was_pressed[keydata.key])
		ctx->flags = ft_bit_set(ctx->flags, g_was_pressed[keydata.key]);
}
