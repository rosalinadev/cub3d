/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:07 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/17 07:37:46 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//# include "defaults.h"

//# include <stdlib.h>
//# include <unistd.h>
//# include <stdio.h>
//# include <fcntl.h>
//# include <math.h>

# include "MLX42/MLX42.h"
//# include "libft.h"

# include "assets.h"
# include "font.h"
# include "input.h"
# include "map.h"
# include "types.h"

typedef struct s_ctx
{
	char		*path;
	t_map		map;
	t_asset		assets[A__SIZE];
	t_font		font;
	mlx_t		*mlx;
	t_vec2		size;
	mlx_image_t	*disp;
	mlx_image_t	*debug;
	t_kb		kb;
}	t_ctx;

/*
// asset_loader.c
int			load_assets(t_ctx *ctx);

// entities.c
bool		init_entities(t_map *map, t_coords c, unsigned int depth);
void		set_map_weights(t_map *map, t_coords c, int depth);
int			iter_entities_variant(t_ctx *ctx,
				int (*f)(t_ctx *, t_entity *, unsigned int));
t_entity	*get_random_enemy(t_map *map);

// movement.c
bool		move_player(t_ctx *ctx, t_flags flags);
void		move_enemies(t_ctx *ctx);

// hooks.c
void		ft_hook_key(mlx_key_data_t keydata, void *param);

// ==== Drawing & rendering ====
# define CSIZE 48
# define FRAME_TIME 0.160
# define MOVE_TIME 0.150
# define ANIM_TIME 0.100

// drawer.c
int			draw_map(t_ctx *ctx);
int			draw_entity_variant(t_ctx *ctx, t_entity *entity,
				unsigned int variant);

// renderer.c
void		update_frame(t_ctx *ctx, double time);
int			update_entity_variant(t_ctx *ctx, t_entity *entity,
				unsigned int variant);
void		render_entities(t_ctx *ctx, double curr);

*/

// loop.c
void		hook_loop(void *param);

#endif
