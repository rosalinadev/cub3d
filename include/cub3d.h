/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:07 by rvandepu          #+#    #+#             */
/*   Updated: 2025/04/04 09:39:16 by rvandepu         ###   ########.fr       */
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
//# include "ft_bitwise.h"

# include "map.h"

/*typedef struct s_entity
{
	t_coords		oc;
	t_coords		c;
	t_cell_type		t;
	bool			m;
	int				i[3][32];
	unsigned char	f;
	double			lm;
}	t_entity;*/

typedef struct s_asset
{
	union
	{
		struct
		{
			char	*name;
			t_col	color;
		}			s_meta;
		mlx_image_t	*img[32];
	};
	bool	is_entity;
	bool	has_variants;
}	t_asset;

typedef unsigned int	t_flags;
typedef enum e_flag
{
	H_UP = 1,
	H_DOWN,
	H_LEFT,
	H_RIGHT,
	P_UP,
	P_DOWN,
	P_LEFT,
	P_RIGHT,
	P_PAUSE,
	P_QUIT,
}	t_flag;

typedef struct s_ctx
{
	char		*path;
	mlx_t		*mlx;
	mlx_image_t	*bg;
	t_map		map;
	t_asset		assets[3][C_MAXTYPE];
	t_font		font;
	mlx_image_t	*counter;
	mlx_image_t	*gametext;
	int			width;
	int			height;
	t_flags		flags;
}	t_ctx;

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

// loop.c
void		putnbr_buf(unsigned int n, char b[11]);
void		ft_hook_loop(void *param);

#endif
