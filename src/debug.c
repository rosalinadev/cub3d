/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 06:08:23 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/19 10:05:34 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

#include "cub3d.h"

#define I 11
#define F 23

static void	ftoa_cat(float f, char *str, size_t l)
{
	char	tmp[I + 1];
	float	i;

	if (f < 0)
		ft_strlcat(str, "-", l);
	f = modff(fabsf(f), &i);
	ft_itoa_buf(i, tmp);
	ft_strlcat(str, tmp, l);
	ft_strlcat(str, ".", l);
	i = (ft_itoa_buf(f *= 10, tmp), f = modff(f, &i), ft_strlcat(str, tmp, l));
	i = (ft_itoa_buf(f *= 10, tmp), f = modff(f, &i), ft_strlcat(str, tmp, l));
	i = (ft_itoa_buf(f *= 10, tmp), f = modff(f, &i), ft_strlcat(str, tmp, l));
	i = (ft_itoa_buf(f *= 10, tmp), f = modff(f, &i), ft_strlcat(str, tmp, l));
}

#define L10 "uptime: "
#define L20 "\npos x: "
#define L21 " y: "
#define L30 "\ndir x: "
#define L31 " y: "

void	draw_debug(t_ctx *ctx)
{
	t_vec2u	c;
	char	str[sizeof(L10) + I + sizeof(L20) + F + sizeof(L21) + F + 1];
	char	b[I + 1];

	ft_bzero(ctx->debug->pixels, ctx->debug->width * ctx->debug->height * 4);
	ft_bzero(str, sizeof(str));
	ft_strlcat(str, L10, sizeof(str));
	ft_itoa_buf(mlx_get_time(), b);
	ft_strlcat(str, b, sizeof(str));
	ft_strlcat(str, L20, sizeof(str));
	ftoa_cat(ctx->player.pos.x, str, sizeof(str));
	ft_strlcat(str, L21, sizeof(str));
	ftoa_cat(ctx->player.pos.y, str, sizeof(str));
	ft_strlcat(str, L30, sizeof(str));
	ftoa_cat(ctx->player.dir.x, str, sizeof(str));
	ft_strlcat(str, L21, sizeof(str));
	ftoa_cat(ctx->player.dir.y, str, sizeof(str));
	c = str_size(&ctx->font, str);
	if (c.x)
		draw_str(ctx->debug, &ctx->font, str, (t_vec2u){0, 0});
}
