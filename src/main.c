/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:57:19 by rvandepu          #+#    #+#             */
/*   Updated: 2025/04/04 09:39:53 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include "cub3d.h"
#include "defaults.h"
#include "error.h"

/*
	[E_OPEN] = "Could not open file.", \
	[E_MEM] = "Memory allocation failed.", \
	[E_MAPWIDTH] = "Map has lines of different width.", \
	[E_EXITREACH] = "Exit is unreachable.", \
	[E_COLLECTREACH] = "At least one collectible is unreachable.", \
	[E_MLX] = "Failed to create window.", \
	[E_PNG] = "Could not load texture.", \
	[E_IMG] = "Could not display image on window.", \
*/

// TODO usage text
// TODO parse _bonus filetype
static bool	parse_args(t_map *map, int argc, char *argv[])
{
	char	*s;

	s = NAME;
	if (argv[0] != NULL)
		s = argv[0];
	if (argc < 2)
		return (printf("Usage: %s <map."MAP_EXT">\n\n" \
						"Keybindings:\n" \
						"\tWASD: move (or HJKL or arrows)\n" \
						"\tSpace: pause\n" \
						"\tEscape: exit\n", \
						s), false);
	s = ft_strrchr(argv[1], '.');
	if (s == NULL || (ft_strcmp(s, "."MAP_EXT) != 0
			&& ft_strcmp(s, "."MAP_EXT"_bonus") != 0))
		return (eno(E_MAP_EXT), false);
	if (ft_strcmp(s, "."MAP_EXT"_bonus") == 0)
		map->is_bonus = true;
	return (true);
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

// FIXME:
//  - refactor everything into modular code
//  - fixup errors to use new codebase
//  - remember to free gnl on error
// TODO:
//  - map loading:
//   - parameter parsing
//   - load assets now or later?
//	 - sprites
//  - load assets
//  - debug mode!
//  - rendering
//  - textures
//  - animated sprites
//  - fixup input, add mouse
//  - minimap (follows player if too big)
int	main(int argc, char *argv[])
{
	t_ctx	ctx;

	ft_bzero(&ctx, sizeof(t_ctx));
	if (!parse_args(&ctx.map, argc, argv))
		return (err_p(1, "While parsing arguments"), EXIT_FAILURE);
	if (!load_map(&ctx.map, argv[1]))
		return (err_p(1, "While loading map"), EXIT_FAILURE);
	/*
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
	*/
	return (EXIT_SUCCESS);
}
