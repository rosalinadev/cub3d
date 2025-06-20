/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 06:08:23 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/20 19:35:36 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

#include "cub3d.h"
#include "mlx_utils.h"

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

#define L10 "fps: "
#define L20 "\npos x: "
#define L21 " y: "
#define L30 "\ndir x: "
#define L31 " y: "

void	draw_debug(t_ctx *ctx, double frametime)
{
	t_vec2u	c;
	char	str[sizeof(L10) + F + sizeof(L20) + F + sizeof(L21) + F + 1];

	mlx_clear_image(ctx->debug);
	ft_bzero(str, sizeof(str));
	ft_strlcat(str, L10, sizeof(str));
	ftoa_cat(1 / frametime, str, sizeof(str));
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
