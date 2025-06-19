/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:28:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/19 08:30:55 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "assets.h"
#include "error.h"

static bool	load_asset(t_asset *asset)
{
	asset->tex = mlx_load_png(asset->path);
	if (!asset->tex)
		return (eno(E_TEX), err_p(2, "While loading PNG asset", asset->path),
			eno(E__NOPRINT), false);
	free(asset->path);
	return (true);
}

void	free_assets(t_asset assets[A__SIZE])
{
	t_asset_id	id;

	id = A__FIRST;
	while (id < A__SIZE)
	{
		free(assets[id].path);
		if (assets[id].tex)
			mlx_delete_texture(assets[id].tex);
		id++;
	}
}

bool	load_assets(t_asset assets[A__SIZE])
{
	t_asset_id	id;

	id = A__FIRST;
	while (id < A__SIZE)
		if (!load_asset(&assets[id]))
			return (free_assets(assets), false);
	return (true);
}
