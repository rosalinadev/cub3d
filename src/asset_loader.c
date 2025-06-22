/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:28:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/22 12:14:49 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"

#include "assets.h"
#include "error.h"

static bool	load_asset(char *path, mlx_texture_t **ret)
{
	mlx_texture_t	*tex;
	uint32_t		*pixels;
	size_t			i;

	if (!path)
		return (true);
	tex = mlx_load_png(path);
	if (!tex)
		return (eno(E_TEX), err_p(2, "While loading PNG asset", path),
			eno(E__NOPRINT), false);
	pixels = malloc(tex->width * tex->height * 4);
	if (!pixels)
		return (eno(E_MEM), err_p(2, "While loading PNG asset", path),
			eno(E__NOPRINT), mlx_delete_texture(tex), false);
	i = tex->width * tex->height;
	while (i--)
		pixels[i % tex->width * tex->height + i / tex->width] = ((uint32_t *)
				tex->pixels)[i / tex->width * tex->width + i % tex->width];
	free(tex->pixels);
	tex->pixels = (uint8_t *)pixels;
	*ret = tex;
	return (true);
}

void	free_assets(t_assets *assets)
{
	t_side	id;
	size_t	i;

	if (assets->font.tex)
		mlx_delete_texture(assets->font.tex);
	assets->font.tex = NULL;
	id = A__SIZE;
	while (id-- != A__FIRST)
	{
		free(assets->meta.path[id]);
		assets->meta.path[id] = NULL;
		if (assets->tex[id])
			mlx_delete_texture(assets->tex[id]);
		assets->tex[id] = NULL;
	}
	free(assets->meta.sprite_dir);
	assets->meta.sprite_dir = NULL;
	if (!assets->sprite)
		return ;
	i = assets->meta.sprite_frames;
	while (assets->sprite && i--)
		if ((assets->sprite + i)->tex)
			mlx_delete_texture((assets->sprite + i)->tex);
	free(assets->sprite);
	assets->sprite = NULL;
}

bool	load_assets(t_assets *assets)
{
	t_side	id;

	if (!init_font(&assets->font))
		return (false);
	id = A__SIZE;
	while (id-- != A__FIRST)
		if (!load_asset(assets->meta.path[id], &assets->tex[id]))
			return (free_assets(assets), false);
	// TODO load sprite frames
	return (true);
}
