/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:57:19 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/27 15:53:17 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	parse_args(t_ctx *ctx, int argc, char *argv[])
{
	char	*ext;

	if (argc < 2)
		return (ft_printf("Usage: %s <file>\n\n" \
							"Keybindings:\n" \
							"	WASD: move\n" \
							"	F11: toggle fullscreen\n" \
							"	Escape: exit\n", \
							*argv), \
						-1);
	ctx->path = *++argv;
	ext = ft_strrchr(*argv, '.');
	if (ext == NULL || ft_strcmp(ext, ".ber") != 0)
		return (-1);
	return (0);
}

static int	init_win(t_ctx *ctx)
{
	ctx->width = ctx->map->width * CSIZE;
	ctx->height = ctx->map->height * CSIZE;
	ctx->mlx = mlx_init(ctx->width, ctx->height, "so_long", false);
	if (!ctx->mlx)
		return (free_map(ctx->map), -1);
	ctx->bg = mlx_new_image(ctx->mlx, 1, 1);
	if (ctx->bg == NULL || (mlx_put_pixel(ctx->bg, 0, 0, 0x080808FF), false)
		|| !mlx_resize_image(ctx->bg, ctx->width, ctx->height)
		|| mlx_image_to_window(ctx->mlx, ctx->bg, 0, 0) < 0)
		return (mlx_terminate(ctx->mlx), -1);
	mlx_key_hook(ctx->mlx, &ft_hook_key, ctx);
	mlx_loop_hook(ctx->mlx, &ft_hook_loop, ctx);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_ctx	ctx;

	ft_bzero(&ctx, sizeof(t_ctx));
	if (parse_args(&ctx, argc, argv) < 0)
		return (EXIT_FAILURE);
	if (load_map(&ctx) < 0)
		return (EXIT_FAILURE);
	if (init_win(&ctx) < 0)
		return (free_map(ctx.map), EXIT_FAILURE);
	if (load_assets(&ctx) < 0 || draw_map(&ctx) < 0 || draw_entities(&ctx) < 0)
		return (free_map(ctx.map), mlx_terminate(ctx.mlx), EXIT_FAILURE);
	mlx_loop(ctx.mlx);
	mlx_terminate(ctx.mlx);
	free_map(ctx.map);
	return (EXIT_SUCCESS);
}
