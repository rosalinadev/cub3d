/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:39:48 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/19 00:13:13 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include <stdint.h>
# include "MLX42/MLX42.h"

# include "font.h"
# include "side.h"

// 11 for int and 4 for ".png"
# define FRAME_SIZE 15

typedef struct s_meta
{
	char		*path[A__SIZE];
	char		*sprite_dir;
	uint32_t	sprite_frames;
	t_col		ceil;
	t_col		floor;
}	t_meta;

typedef struct s_frame
{
	struct s_frame	*next;
	mlx_texture_t	*tex;
}	t_frame;

typedef struct s_assets
{
	t_font			font;
	t_meta			meta;
	mlx_texture_t	*tex[A__SIZE];
	t_frame			*sprite;
	uint32_t		ceil;
	uint32_t		floor;
}	t_assets;

// metadata_parser.c
bool	parse_meta(int fd, t_meta *meta, bool is_bonus);

// asset_loader.c
void	free_assets(t_assets *assets);
bool	load_assets(t_assets *assets, bool is_bonus);

#endif
