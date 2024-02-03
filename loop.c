/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 12:10:25 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/03 22:55:37 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*static void	move(t_ctx *ctx)
{
	static double	last_time = 0;
	double			time;
	double			upf;

	time = mlx_get_time();
	upf = (time - last_time) * 100 / ctx->zoom;
	if (ft_bit_check(ctx->flags, F_UP))
		ctx->trans.z -= upf;
	else if (ft_bit_check(ctx->flags, F_DOWN))
		ctx->trans.z += upf;
	if (ft_bit_check(ctx->flags, F_LEFT))
		ctx->trans.x -= upf;
	else if (ft_bit_check(ctx->flags, F_RIGHT))
		ctx->trans.x += upf;
	if (ft_bit_check(ctx->flags, F_UP))
		ctx->trans.y += upf;
	else if (ft_bit_check(ctx->flags, F_DOWN))
		ctx->trans.y -= upf;
	last_time = time;
}*/

static void	set_frame(t_asset *asset, bool enabled)
{
	unsigned char	variant;

	variant = 1;
	if (asset->has_variants)
		variant = 16;
	while (variant--)
		if (asset->img[variant])
			asset->img[variant]->enabled = enabled;
}

void	update_frame(t_ctx *ctx, double time)
{
	static double			last_time = 0;
	static unsigned char	frame = 0;
	unsigned char			i;
	unsigned char			j;

	if (!last_time)
		return ((void)(last_time = time));
	if (time - last_time < 0.160)
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

void	ft_hook_loop(void *param)
{
	t_ctx	*ctx;
	double	time;

	ctx = param;
	time = mlx_get_time();
	update_frame(ctx, time);
	/*move(ctx);
	ft_bzero(ctx->bg->pixels, ctx->width * ctx->height * 4);
	traverse(ctx, (t_coords){0, 0}, ctx->map->values, NULL);*/
	if (ft_bit_check(ctx->flags, F_QUIT))
		mlx_close_window(ctx->mlx);
}
