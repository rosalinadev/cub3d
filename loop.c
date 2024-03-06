/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:10:25 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/06 16:03:34 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static inline void	set_frame(t_asset *asset, bool enabled)
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

static inline void	update_frame(t_ctx *ctx, double time)
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

static inline t_flags	interpret_input(t_flags *flags)
{
	static t_flags	last_flags;
	t_flags			out;

	last_flags &= ~(0b1111 << P_UP) | (*flags & 0b1111 << H_UP) << 4;
	last_flags &= ~(0b1111 << H_UP) | (*flags & last_flags & 0b1111 << H_UP);
	out = *flags & ~(0b11111111 << H_UP);
	if (*flags & 0b1111 << P_UP)
	{
		if (!(last_flags & 0b1111 << H_UP))
		{
			last_flags |= (*flags & 0b1111 << P_UP) >> 4;
			out |= *flags & 0b1111 << P_UP;
		}
		else if (!(last_flags & 0b1111 << P_UP))
			last_flags |= *flags & 0b1111 << P_UP;
		else
			*flags &= ~(0b1111 << P_UP);
	}
	if (!(last_flags & 0b1111 << H_UP) && (last_flags & 0b1111 << P_UP))
	{
		last_flags |= (last_flags & 0b1111 << P_UP) >> 4;
		last_flags &= ~(0b1111 << P_UP);
	}
	*flags &= ~(0b1111 << P_UP);
	return (out | (*flags & last_flags & 0b1111 << H_UP));
}

// TODO
void	ft_hook_loop(void *param)
{
	t_ctx			*ctx;
	static double	last_move_time;
	t_flags			flags;

	ctx = param;
	update_frame(ctx, mlx_get_time());
	flags = interpret_input(&ctx->flags);
	if (ctx->map->gamestate == G_PLAYING && \
		(flags & 0b1111 << P_UP || (flags & 0b1111 << H_UP \
			&& mlx_get_time() - last_move_time >= MOVE_TIME)))
	{
		clear_mem(ctx->map);
		set_map_weights(ctx->map, ctx->map->player->c, 1);
		move_player(ctx, flags);
		move_enemies(ctx->map);
		iter_entities_variant(ctx, update_entity_variant);
		last_move_time = mlx_get_time();
	}
	render_entities(ctx, mlx_get_time());
	if (ft_bit_check(flags, P_QUIT))
		mlx_close_window(ctx->mlx);
}
