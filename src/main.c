/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:57:19 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/18 06:30:05 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include "cub3d.h"
#include "defaults.h"
#include "error.h"

// TODO usage text
static bool	parse_args(t_map *map, int argc, char *argv[])
{
	char	*s;

	s = NAME;
	if (argv[0] != NULL)
		s = argv[0];
	if (argc < 2)
		return (((printf("Usage: %s map"MAP_EXT"(_bonus)\n\n"
						"Keybindings:\n"
						"\tWASD: move\n"
						"\tMouse: look left/right\n"
						"\tEscape: exit\n",
						s))), eno(E__NOPRINT), false);
	s = ft_strrchr(argv[1], MAP_EXT[0]);
	if (s == NULL || (ft_strcmp(s, MAP_EXT) != 0
			&& ft_strcmp(s, MAP_EXT"_bonus") != 0))
		return (eno(E_MAP_EXT), false);
	map->is_bonus = ft_strcmp(s, MAP_EXT"_bonus") == 0;
	if (map->is_bonus) // TODO remove when implemented
		return (eno(E_BONUS), false);
	return (true);
}

static bool	init_img(t_ctx *ctx)
{
	ctx->disp = mlx_new_image(ctx->mlx, ctx->size.x, ctx->size.y);
	ctx->debug = mlx_new_image(ctx->mlx, ctx->size.x, ctx->size.y);
	if (!ctx->disp || !ctx->debug)
		return (eno(E_IMG), false);
	if (mlx_image_to_window(ctx->mlx, ctx->disp, 0, 0) < 0
		|| mlx_image_to_window(ctx->mlx, ctx->debug, 0, 0) < 0)
		return (eno(E_DISP), false);
	if (!init_font(&ctx->font))
		return (false);
	return (true);
}

/* TODO remove or properly implement and move to other file
static bool	get_win_size(t_vec2 *size, bool fullscreen)
{
	mlx_t	*mlx;

	size->x = WIDTH;
	size->y = HEIGHT;
	if (fullscreen)
	{
		mlx_set_setting(MLX_FULLSCREEN, false);
		mlx_set_setting(MLX_HEADLESS, true);
		mlx = mlx_init(size->x, size->y, NAME, false);
		if (!mlx)
			return (eno(E_MLX), false);
		mlx_get_monitor_size(0, &size->x, &size->y);
		mlx_terminate(mlx);
		mlx_set_setting(MLX_HEADLESS, false);
	}
	return (true);
}*/

static bool	init_win(t_ctx *ctx)
{
	static bool	fullscreen = START_FULLSCREEN;

	//if (ft_bit_check(ctx->flags, F_FULLSCREEN))
	//	fullscreen = !fullscreen;
	//if (!get_win_size(ctx, fullscreen))
	//if (!get_win_size(&ctx->size, fullscreen))
	//	return (false);
	ctx->size = (t_vec2){WIDTH, HEIGHT};
	mlx_set_setting(MLX_FULLSCREEN, fullscreen);
	ctx->mlx = mlx_init(ctx->size.x, ctx->size.y, NAME, !fullscreen);
	if (!ctx->mlx)
		return (eno(E_MLX), false);
	if (!init_img(ctx))
		return (false);
	//ctx->flags = ft_bit_clear(ctx->flags, F_FULLSCREEN);
	//mlx_resize_hook(ctx->mlx, &ft_hook_resize, ctx);
	mlx_key_hook(ctx->mlx, &hook_key, &ctx->kb);
	//mlx_scroll_hook(ctx->mlx, &ft_hook_scroll, ctx);
	//mlx_mouse_hook(ctx->mlx, &ft_hook_mouse, ctx);
	//mlx_cursor_hook(ctx->mlx, &ft_hook_cursor, ctx);
	mlx_loop_hook(ctx->mlx, &hook_loop, ctx);
	return (true);
}

static void	cleanup(t_ctx *ctx)
{
	free(ctx->map.cells);
	free_assets(ctx->assets);
	if (ctx->mlx)
		mlx_terminate(ctx->mlx);
	if (ctx->font.tex)
		mlx_delete_texture(ctx->font.tex);
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
//  - load assets XXX free
//  - debug mode!
//  - rendering
//  - textures
//  - animated sprites
//  - fixup input, add mouse
//  - minimap (follows player if too big)
// XXX possible future improvements: 
// - fullscreen key
// - dynamic resize support
// XXX future issues
// - correctly scaling dir and plane vects
// - correctly scaling sprite distance

int	main(int argc, char *argv[])
{
	static t_ctx	ctx;

	if (!parse_args(&ctx.map, argc, argv))
		return (err_p(1, "While parsing arguments"), EXIT_FAILURE);
	if (!load_map(&ctx.map, argv[1]))
		return (err_p(1, "While loading map"), EXIT_FAILURE);
	player_respawn(&ctx.player, &ctx.map);
	printf("player pos x:%f y:%f\n", ctx.player.pos.x, ctx.player.pos.y);
	printf("player dir x:%f y:%f\n", ctx.player.dir.x, ctx.player.dir.y);
	// load assets
	// load sprites
	//t_vec2u (pos) = sprite_pos(&ctx.map,
	//	&get_cell(&ctx.map, (t_vec2){5, 2})->sprite);
	//printf("sprite x:%u y:%u\n", pos.x, pos.y);
	printf("width:%u height:%u\n", ctx.map.size.x, ctx.map.size.y);
	printf("spawn pos x:%u y:%u\n", ctx.map.spawn_pos.x, ctx.map.spawn_pos.y);
	printf("spawn dir x:%f y:%f\n", ctx.map.spawn_facing.x,
		ctx.map.spawn_facing.y);
	//printf("is bonus: %d\n", ctx.map.is_bonus);
	if (!init_win(&ctx))
		return (err_p(1, "While creating window"), cleanup(&ctx), EXIT_FAILURE);
	/*
	if (load_assets(&ctx) < 0 || draw_map(&ctx) < 0
		|| iter_entities_variant(&ctx, draw_entity_variant) < 0
		|| !init_font(&ctx))
		return (free_map(ctx.map), mlx_terminate(ctx.mlx),
			printerr(), EXIT_FAILURE);
	mlx_delete_texture(ctx.font.img);
	free_map(ctx.map);
	*/
	printf("screen width:%u height:%u\n", ctx.size.x, ctx.size.y);
	mlx_loop(ctx.mlx);
	cleanup(&ctx);
	return (EXIT_SUCCESS);
}
