/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:07 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/10 16:30:03 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# include "MLX42/MLX42.h"
# include "libft.h"
# include "ft_bitwise.h"

typedef enum e_errno
{
	E_FILENAME = 1,
	E_OPEN,
	E_MEM,
	E_MAPEMPTY,
	E_MAPWIDTH,
	E_MAPEDGES,
	E_MAPCONTENTS,
	E_EXITREACH,
	E_COLLECTREACH,
	E_MLX,
	E_FONT,
	E_PNG,
	E_IMG,
}	t_errno;

extern t_errno			g_eno;

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
	bool			m;
	int				i[3][32];
	unsigned char	f;
	t_facing		d;
	double			lm;
}	t_entity;

typedef enum e_gamestate
{
	G_PLAYING = 0,
	G_PAUSED,
	G_LOST,
	G_WON,
}	t_gamestate;

typedef struct s_map
{
	char			**r;
	t_cell			**c;
	unsigned int	width;
	unsigned int	height;
	unsigned int	collectibles;
	unsigned int	movecount;
	t_gamestate		gamestate;
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
	bool	is_entity;
	bool	has_variants;
}	t_asset;

typedef struct s_char
{
	t_coords	p;
	t_coords	s;
}	t_char;

typedef struct s_font
{
	mlx_texture_t	*img;
	t_char			meta['~' - ' ' + 1];
	unsigned char	sc;
}	t_font;

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
	t_map		*map;
	t_asset		assets[3][C_MAXTYPE];
	t_font		font;
	mlx_image_t	*counter;
	mlx_image_t	*gametext;
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
bool		move_player(t_ctx *ctx, t_flags flags);
void		move_enemies(t_ctx *ctx);

// hooks.c
void		ft_hook_key(mlx_key_data_t keydata, void *param);

// Drawing & rendering
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

// font.c
bool		init_font(t_ctx *ctx);
t_coords	str_size(t_font *font, const char *str);
bool		draw_str(mlx_image_t *img, t_font *font, const char *str,
				t_coords pos);

// loop.c
void		putnbr_buf(unsigned int n, char b[11]);
void		ft_hook_loop(void *param);

#endif
