/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:39:48 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/22 12:13:37 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include <stdint.h>
# include "MLX42/MLX42.h"

# include "font.h"
# include "side.h"

typedef struct s_meta
{
	char		*path[A__SIZE];
	char		*sprite_dir;
	uint32_t	sprite_frames;
	uint32_t	ceil;
	uint32_t	floor;
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
}	t_assets;

// asset_loader.c
void	free_assets(t_assets *assets);
bool	load_assets(t_assets *assets);

#endif
