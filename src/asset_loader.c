/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:28:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/20 20:20:48 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"

#include "assets.h"
#include "error.h"
#include "mlx_utils.h"

// https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
static inline uint32_t	round_up_pow2(uint32_t v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return (v);
}

static bool	scale_tex(mlx_texture_t **tex)
{
	uint32_t		width;
	uint32_t		height;
	mlx_texture_t	*newtex;

	printf("[scale] old: %d %d\n", (*tex)->width, (*tex)->height);
	width = round_up_pow2((*tex)->width);
	height = round_up_pow2((*tex)->height);
	if ((*tex)->width == width && (*tex)->height == height)
		return (true);
	printf("[scale] new: %d %d\n", width, height);
	newtex = mlx_new_texture(width, height);
	if (!newtex)
		return (eno(E_TEX), false);
	mlx_scale_texture(*tex, newtex);
	mlx_delete_texture(*tex);
	*tex = newtex;
	return (true);
}

// caller handles freeing after errors
static bool	load_asset(t_asset *asset)
{
	asset->tex = mlx_load_png(asset->path);
	if (!asset->tex)
		return (eno(E_TEX), err_p(2, "While loading PNG asset", asset->path),
			eno(E__NOPRINT), false);
	free(asset->path);
	asset->path = NULL;
	//if (!scale_tex(&asset->tex))
	//	return (false);
	return (true);
}

void	free_assets(t_asset assets[A__SIZE])
{
	t_asset_id	id;

	id = A__FIRST;
	while (id < A__SIZE)
	{
		free(assets[id].path);
		assets[id].path = NULL;
		if (assets[id].tex)
			mlx_delete_texture(assets[id].tex);
		assets[id].tex = NULL;
		id++;
	}
}

bool	load_assets(t_asset assets[A__SIZE])
{
	t_asset_id	id;

	id = A__FIRST;
	while (id < A__SIZE)
		if (!load_asset(&assets[id++]))
			return (free_assets(assets), false);
	return (true);
}
