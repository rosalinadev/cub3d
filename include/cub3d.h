/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:07 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/27 21:37:58 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"

# include "assets.h"
# include "input.h"
# include "map.h"
# include "player.h"
# include "raycast.h"
# include "types.h"

typedef struct s_ctx
{
	char		*path;
	t_map		map;
	t_player	player;
	t_assets	assets;
	mlx_t		*mlx;
	t_vec2		size;
	t_raycast	ray;
	mlx_image_t	*disp;
	mlx_image_t	*debug;
	mlx_image_t	*text;
	t_kb		kb;
	bool		paused;
	uint8_t		ignore_mouse;
}	t_ctx;

// renderer.c
void	render_screen(t_ctx *ctx);

// debug.c
void	draw_debug(t_ctx *ctx, double frametime);

// loop.c
void	hook_loop(void *param);

#endif
