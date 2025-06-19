/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:39:48 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/19 08:27:40 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include "MLX42/MLX42.h"

# include "raycast.h"

// keep in sync with raycast.h:e_side
typedef enum e_asset_id
{
	A__FIRST = SIDE_W,
	A_W = A__FIRST,
	A_E,
	A_N,
	A_S,
	A__SIZE
}	t_asset_id;

typedef struct s_asset
{
	char			*path;
	mlx_texture_t	*tex;
}	t_asset;

// asset_loader.c
void	free_assets(t_asset assets[A__SIZE]);
bool	load_assets(t_asset assets[A__SIZE]);

#endif
