/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:12:02 by rvandepu          #+#    #+#             */
/*   Updated: 2025/05/09 16:20:48 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ft_bitwise.h"

#include "input.h"

#define MAXKEYCODE 350

static const t_kb_bit	g_is_pressed[MAXKEYCODE] = {
[MLX_KEY_W] = H_FORWARDS,
[MLX_KEY_A] = H_LEFT,
[MLX_KEY_S] = H_BACKWARDS,
[MLX_KEY_D] = H_RIGHT,
[MLX_KEY_LEFT] = H_LOOKLEFT,
[MLX_KEY_RIGHT] = H_LOOKRIGHT,
};

static const t_kb_bit	g_was_pressed[MAXKEYCODE] = {
[MLX_KEY_ESCAPE] = P_QUIT,
[MLX_KEY_M] = P_MINIMAP,
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
