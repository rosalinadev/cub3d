/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:07 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/01 22:32:15 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

//# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "MLX42/MLX42.h"
# include "libft.h"
# include "ft_bitwise.h"

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef union color
{
	unsigned int	col;
	unsigned char	rgba[4];
}	t_col;

typedef struct s_coords
{
	unsigned int	x;
	unsigned int	y;
}	t_coords;

typedef enum e_cell_type
{
	C_EMPTY = 1,
	C_WALL,
	C_COLLECTIBLE,
	C_EXIT,
	C_PLAYER,
	C_ENEMY,
	C_MAXTYPE
}	t_cell_type;

typedef unsigned char	t_variant;
typedef enum e_facing
{
	F_WEST,
	F_NORTH,
	F_EAST,
	F_SOUTH,
}	t_facing;

typedef struct s_cell
{
	t_cell_type	t;
	t_variant	v;
	int			i[3];
}	t_cell;

typedef struct s_entity
{
	t_coords		oc;
	t_coords		c;
	t_cell_type		t;
	int				i[3][32];
	unsigned char	f;
	t_facing		d;
}	t_entity;

typedef struct s_map
{
	char			**r;
	t_cell			**c;
	unsigned int	width;
	unsigned int	height;
	unsigned int	collectibles;
	unsigned int	num_entities;
	t_entity		*entities;
	t_entity		*player;
	bool			has_player;
	bool			has_exit;
	int				**mem;
}	t_map;

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
	bool		is_entity;
	bool		has_variants;
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
	P_QUIT,
}	t_flag;

typedef struct s_ctx
{
	char		*path;
	mlx_t		*mlx;
	mlx_image_t	*bg;
	t_map		*map;
	t_asset		assets[3][C_MAXTYPE];
	int			width;
	int			height;
	t_flags		flags;
}	t_ctx;

// map_loader.c
void		free_map(t_map *map);
int			load_map(t_ctx *fdf);

// map_utils.c
bool		alloc_mem(t_map *map, unsigned int depth);
void		clear_mem(t_map *map);
void		free_mem(t_map *map);
bool		map_is_valid(t_map *map);

// asset_loader.c
int			load_assets(t_ctx *ctx);

// entities.c
bool		init_entities(t_map *map, t_coords c, unsigned int depth);
void		set_map_weights(t_map *map, t_coords c, int depth);
int			iter_entities_variant(t_ctx *ctx,
				int (*f)(t_ctx *, t_entity *, unsigned int));
t_entity	*get_random_enemy(t_map *map);

// movement.c
void		move_player(t_ctx *ctx);
void		move_enemies(t_ctx *ctx);

// hooks.c
void		ft_hook_key(mlx_key_data_t keydata, void *param);

// loop.c
void		ft_hook_loop(void *param);

// renderer.c
# define CSIZE 48
# define FRAME_TIME 0.160
# define MOVE_TIME 0.100

int			draw_map(t_ctx *ctx);
int			draw_entity_variant(t_ctx *ctx, t_entity *entity,
				unsigned int variant);
int			update_entity_variant(t_ctx *ctx, t_entity *entity,
				unsigned int variant);
void		render_entities(t_ctx *ctx, double start, double curr);

#endif
