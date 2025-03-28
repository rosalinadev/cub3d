/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:10:25 by rvandepu          #+#    #+#             */
/*   Updated: 2025/03/28 02:50:17 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	putnbr_buf(unsigned int n, char b[11])
{
	int		i;
	int		j;

	ft_bzero(b, 11);
	i = 9;
	while (n != 0)
	{
		b[i--] = '0' + n % 10;
		n /= 10;
	}
	if (i == 9)
		b[9] = '0';
	i = 0;
	j = 0;
	while (i < 10)
		if (b[i++])
			b[j++] = b[i - 1];
	b[j] = '\0';
}

static inline void	draw_movecount(t_ctx *ctx)
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
}

static inline void	draw_gamestate(t_ctx *ctx)
{
	static t_gamestate	old_gamestate;
	t_coords			c;
	char				str[15];

	if (ctx->map->gamestate != old_gamestate)
	{
		ft_bzero(ctx->gametext->pixels,
			ctx->gametext->width * ctx->gametext->height * 4);
		ft_bzero(str, 15);
		if (ctx->map->gamestate == G_PAUSED)
			ft_strlcat(str, "Game paused...", 15);
		else if (ctx->map->gamestate == G_LOST)
			ft_strlcat(str, "You lost :c", 15);
		else if (ctx->map->gamestate == G_WON)
			ft_strlcat(str, "You won! :D", 15);
		c = str_size(&ctx->font, str);
		if (c.x && c.x < ctx->gametext->width && c.y < ctx->gametext->height)
			draw_str(ctx->gametext, &ctx->font, str, (t_coords){(ctx->gametext \
				->width - c.x) / 2 - 1, (ctx->gametext->height - c.y) / 2 - 1});
		if (ctx->map->gamestate == G_LOST || ctx->map->gamestate == G_WON)
			ft_printf("%s\n", str);
		old_gamestate = ctx->map->gamestate;
	}
}

void	ft_hook_loop(void *param)
{
	t_ctx			*c;
	static double	last_move_time;
	t_flags			flags;

	c = param;
	update_frame(c, mlx_get_time());
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
	draw_movecount(c);
	draw_gamestate(c);
	if (ft_bit_check(flags, P_QUIT))
		mlx_close_window(c->mlx);
}
