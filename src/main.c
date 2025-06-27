/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:57:19 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/27 22:52:44 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "ft_bitwise.h"
#include "libft.h"

#include "cub3d.h"
#include "defaults.h"
#include "error.h"
#include "mlx_utils.h"
#include "types.h"

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
	if (DISABLE_BONUS && map->is_bonus) // TODO remove when implemented
		return (eno(E_BONUS), false);
	return (true);
}

// TODO pull ceil and floor colors from metadata
static bool	init_img(t_ctx *ctx)
{
	mlx_image_t	*bg;

	bg = mlx_new_image(ctx->mlx, 1, 2);
	ctx->disp = mlx_new_image(ctx->mlx, ctx->size.x, ctx->size.y);
	ctx->debug_overlay = mlx_new_image(ctx->mlx, ctx->size.x, ctx->size.y);
	ctx->text = mlx_new_image(ctx->mlx, 1, 1);
	if (!bg || !ctx->disp || !ctx->debug_overlay || !ctx->text)
		return (eno(E_IMG), false);
	mlx_put_pixel(bg, 0, 0, 0x808080FF);
	mlx_put_pixel(bg, 0, 1, 0x404040FF);
	mlx_put_pixel(ctx->text, 0, 0, 0x0000007F);
	if (!mlx_resize_image(bg, ctx->size.x, ctx->size.y)
		|| !mlx_resize_image(ctx->text, ctx->size.x, ctx->size.y))
		return (eno(E_IMG), false);
	if (mlx_image_to_window(ctx->mlx, bg, 0, 0) < 0
		|| mlx_image_to_window(ctx->mlx, ctx->disp, 0, 0) < 0
		|| mlx_image_to_window(ctx->mlx, ctx->text, 0, 0) < 0
		|| mlx_image_to_window(ctx->mlx, ctx->debug_overlay, 0, 0) < 0)
		return (eno(E_DISP), false);
	return (true);
}

#define PAUSED "PAUSED"

static bool	init_win(t_ctx *ctx)
{
	static bool	fullscreen = START_FULLSCREEN;
	t_vec2u		size;

	if (ft_bit_check(ctx->kb, P_FULLSCREEN))
		fullscreen = !fullscreen;
	if (!get_win_size(&ctx->size, fullscreen))
		return (false);
	mlx_set_setting(MLX_FULLSCREEN, fullscreen);
	ctx->mlx = mlx_init(ctx->size.x, ctx->size.y, NAME, !fullscreen);
	if (!ctx->mlx)
		return (eno(E_MLX), false);
	if (!init_img(ctx))
		return (false);
	size = str_size((ctx->assets.font.sc = 2, &ctx->assets.font), PAUSED);
	if (size.x > (uint32_t)ctx->size.x || size.y > (uint32_t)ctx->size.y)
		return (eno(E_SIZE), false);
	draw_str(ctx->text, &ctx->assets.font, PAUSED,
		(t_vec2u){(ctx->size.x - size.x) / 2, (ctx->size.y - size.y) / 2});
	ctx->assets.font.sc = FONT_SCALE;
	ctx->paused ^= true;
	ctx->kb = ft_bit_set(ft_bit_clear(ctx->kb, P_FULLSCREEN), P_PAUSE);
	mlx_key_hook(ctx->mlx, &hook_key, &ctx->kb);
	mlx_cursor_hook(ctx->mlx, &hook_cursor, ctx);
	mlx_loop_hook(ctx->mlx, &hook_loop, ctx);
	return (true);
}

static void	cleanup(t_ctx *ctx)
{
	free(ctx->map.cells);
	ctx->map.cells = NULL;
	free_assets(&ctx->assets);
	if (ctx->mlx)
		mlx_terminate(ctx->mlx);
}

// FIXME:
//  - fixup errors to use new codebase
//  - remember to free gnl on error
// TODO:
//  - map loading:
//   - parameter parsing
//	 - sprites
//  - animated sprites
//  - mouse support:
//   - hide cursor
//   - snap cursor to window center
//   - hook movement into rotation
//   - pause menu to quit window?
//  - minimap (follows player if too big)
// XXX future issues
// - correctly scaling dir and plane vects
// - correctly scaling sprite distance

int	main(int argc, char *argv[])
{
	static t_ctx	ctx;

	if (!parse_args(&ctx.map, argc, argv))
		return (err_p(1, "While parsing arguments"), EXIT_FAILURE);
	if (!load_map(argv[1], &ctx.map, &ctx.assets))
		return (err_p(1, "While loading map"), EXIT_FAILURE);
	player_respawn(&ctx.player, &ctx.map);
	printf("player pos x:%f y:%f\n", ctx.player.pos.x, ctx.player.pos.y);
	printf("player dir x:%f y:%f\n", ctx.player.dir.x, ctx.player.dir.y);
	ctx.assets.meta.path[A_W] = ft_strdup("assets/gradient.png");
	ctx.assets.meta.path[A_E] = ft_strdup("assets/cub3d_test.png");
	ctx.assets.meta.path[A_N] = ft_strdup("assets/checkerboard.png");
	ctx.assets.meta.path[A_S] = ft_strdup("assets/highres.png");
	if (!load_assets(&ctx.assets))
		return (err_p(1, "While loading assets"), cleanup(&ctx), EXIT_FAILURE);
	// load sprites
	printf("width:%u height:%u\n", ctx.map.size.x, ctx.map.size.y);
	printf("spawn pos x:%u y:%u\n", ctx.map.spawn_pos.x, ctx.map.spawn_pos.y);
	printf("spawn dir x:%f y:%f\n", ctx.map.spawn_facing.x,
		ctx.map.spawn_facing.y);
	while (true)
	{
		if (!init_win(&ctx))
			return (err_p(1, "While creating window"),
				cleanup(&ctx), EXIT_FAILURE);
		printf("screen width:%u height:%u\n", ctx.size.x, ctx.size.y);
		mlx_loop(ctx.mlx);
		mlx_terminate(ctx.mlx);
		ctx.mlx = NULL;
		if (!ft_bit_check(ctx.kb, P_FULLSCREEN))
			break ;
	}
	cleanup(&ctx);
	return (EXIT_SUCCESS);
}
