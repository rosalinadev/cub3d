/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:07 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/24 18:39:41 by rvandepu         ###   ########.fr       */
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

typedef unsigned char	t_variants;
typedef enum e_variant
{
	V_WEST,
	V_NORTH,
	V_EAST,
	V_SOUTH,
}	t_variant;

typedef struct s_cell
{
	t_cell_type	t;
	t_variants	v;
}	t_cell;

typedef struct s_map
{
	char			**r;
	t_cell			**c;
	unsigned int	width;
	unsigned int	height;
	t_coords		start;
	unsigned int	collectibles;
	bool			has_exit;
	bool			**mem;
}	t_map;

typedef struct s_args
{
	char	*map_path;
}	t_args;

# define CSIZE 48

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
	F_UP = 1,
	F_DOWN,
	F_LEFT,
	F_RIGHT,
	F_QUIT,
}	t_flag;

typedef struct s_ctx
{
	mlx_t		*mlx;
	mlx_image_t	*bg;
	t_map		*map;
	t_args		args;
	t_asset		assets[3][C_MAXTYPE];
	int			width;
	int			height;
	int			maxsteps;
	t_flags		flags;
}	t_ctx;

// map_loader.c
void			free_map(t_map *map);
int				load_map(t_ctx *fdf);

// map_utils.c
bool			map_is_valid(t_map *map);

// asset_loader.c
int				load_assets(t_ctx *ctx);

// hooks.c
void			ft_hook_key(mlx_key_data_t keydata, void *param);

// loop.c
void			ft_hook_loop(void *param);

// renderer.c
int				draw_static(t_ctx *ctx);

#endif
