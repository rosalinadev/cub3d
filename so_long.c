/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:57:19 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/10 16:19:53 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_errno				g_eno;

static void	printerr(void)
{
	static const char	*errstr[] = {\
		[E_FILENAME] = "Incorrect filename.", \
		[E_OPEN] = "Could not open file.", \
		[E_MEM] = "Memory allocation failed.", \
		[E_MAPEMPTY] = "Map is empty", \
		[E_MAPWIDTH] = "Map has lines of different width.", \
		[E_MAPEDGES] = "Map is not surrounded by walls.", \
		[E_MAPCONTENTS] = "Map has invalid contents.", \
		[E_EXITREACH] = "Exit is unreachable.", \
		[E_COLLECTREACH] = "At least one collectible is unreachable.", \
		[E_MLX] = "Failed to create window.", \
		[E_FONT] = "Could not load font.", \
		[E_PNG] = "Could not load texture.", \
		[E_IMG] = "Could not display image on window.", \
	};

	if (errstr[g_eno])
		ft_fprintf(stderr, "%s\n", errstr[g_eno]);
}

static int	parse_args(t_ctx *ctx, int argc, char *argv[])
{
	char	*ext;

	if (argc < 2)
		return (ft_printf("Usage: %s <map.ber>\n\n" \
							"Keybindings:\n" \
							"	WASD: move (or HJKL or arrows)\n" \
							"	Space: pause\n", \
							"	Escape: exit\n", \
							*argv), \
						-1);
	ctx->path = *++argv;
	ext = ft_strrchr(*argv, '.');
	if (ext == NULL || ft_strcmp(ext, ".ber") != 0)
		return (g_eno = E_FILENAME, -1);
	return (0);
}

static int	init_win(t_ctx *ctx)
{
	ctx->width = ctx->map->width * CSIZE;
	ctx->height = ctx->map->height * CSIZE;
	ctx->mlx = mlx_init(ctx->width, ctx->height, "so_long", false);
	if (!ctx->mlx)
		return (g_eno = E_MLX, -1);
	ctx->bg = mlx_new_image(ctx->mlx, 1, 1);
	if (ctx->bg == NULL || (mlx_put_pixel(ctx->bg, 0, 0, 0x000000FF),
			!mlx_resize_image(ctx->bg, ctx->width, ctx->height)))
		return (g_eno = E_MEM, mlx_terminate(ctx->mlx), -1);
	if (mlx_image_to_window(ctx->mlx, ctx->bg, 0, 0) < 0)
		return (g_eno = E_IMG, mlx_terminate(ctx->mlx), -1);
	mlx_key_hook(ctx->mlx, &ft_hook_key, ctx);
	mlx_loop_hook(ctx->mlx, &ft_hook_loop, ctx);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_ctx	ctx;

	ft_bzero(&ctx, sizeof(t_ctx));
	if (parse_args(&ctx, argc, argv) < 0)
		return (printerr(), EXIT_FAILURE);
	if (load_map(&ctx) < 0)
		return (printerr(), EXIT_FAILURE);
	if (init_win(&ctx) < 0)
		return (free_map(ctx.map), printerr(), EXIT_FAILURE);
	if (load_assets(&ctx) < 0 || draw_map(&ctx) < 0
		|| iter_entities_variant(&ctx, draw_entity_variant) < 0
		|| !init_font(&ctx))
		return (free_map(ctx.map), mlx_terminate(ctx.mlx),
			printerr(), EXIT_FAILURE);
	mlx_loop(ctx.mlx);
	mlx_delete_texture(ctx.font.img);
	mlx_terminate(ctx.mlx);
	free_map(ctx.map);
	return (EXIT_SUCCESS);
}
