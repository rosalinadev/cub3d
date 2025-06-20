/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:07 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/20 22:40:34 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"

# include "assets.h"
# include "font.h"
# include "input.h"
# include "map.h"
# include "player.h"
# include "types.h"

typedef struct s_ctx
{
	char		*path;
	t_map		map;
	t_player	player;
	t_asset		assets[A__SIZE];
	t_font		font;
	mlx_t		*mlx;
	t_vec2		size;
	mlx_image_t	*disp;
	mlx_image_t	*debug;
	t_kb		kb;
}	t_ctx;

// renderer.c
void	render_screen(t_ctx *ctx);

// debug.c
void	draw_debug(t_ctx *ctx, double frametime);

// loop.c
void	hook_loop(void *param);

#endif
