/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:10:25 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/17 13:34:21 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bitwise.h"

#include "cub3d.h"
#include "libft.h"

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

#define DBG1 "uptime: "
#define DBG2 "\nhi"

// TODO replace with fps or something of the sort,
//      F3-like overlay is unimportant
static inline void	draw_debug(t_ctx *ctx)
{
	t_vec2u	c;
	char	str[sizeof(DBG1) + 11 + sizeof(DBG2) + 1];
	char	b[12];

	ft_bzero(ctx->debug->pixels, ctx->debug->width * ctx->debug->height * 4);
	ft_bzero(str, sizeof(str));
	ft_strlcat(str, DBG1, sizeof(str));
	ft_itoa_buf(mlx_get_time(), b);
	ft_strlcat(str, b, sizeof(str));
	ft_strlcat(str, DBG2, sizeof(str));
	c = str_size(&ctx->font, str);
	ft_printf("str:%s b:%s\nsize x:%u y:%u\n", str, b, c.x, c.y);
	if (c.x)
		draw_str(ctx->debug, &ctx->font, str, (t_vec2u){0, 0});
}

static inline void	render_frame(t_ctx *ctx)
{
	static double	last_time = -1;
	double			time;

	time = mlx_get_time();
	if (time - last_time >= 1)
	{
		last_time = time;
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
	render_frame(c);
	if (ft_bit_check(c->kb, P_QUIT))
		mlx_close_window(c->mlx);
}
