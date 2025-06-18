/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:39:48 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/17 08:17:17 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSETS_H
# define ASSETS_H

# include "MLX42/MLX42.h"

typedef enum e_asset_id
{
	A__FIRST = 0,
	A_N = A__FIRST,
	A_W,
	A_S,
	A_E,
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
