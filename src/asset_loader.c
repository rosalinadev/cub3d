/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:28:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/18 01:46:12 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#include "libft.h"

#include "assets.h"
#include "error.h"

static bool	load_asset(char *path, mlx_texture_t **ret)
{
	mlx_texture_t	*tex;
	uint32_t		*pixels;
	size_t			i;

	if (!path)
		return (eno(E_TEXPATH), false);
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
	i = assets->meta.sprite_frames;
	while (assets->sprite && i--)
		if (assets->sprite[i].tex)
			mlx_delete_texture(assets->sprite[i].tex);
	free(assets->sprite);
	assets->sprite = NULL;
}

bool	load_sprites(t_assets *assets)
{
	char		*filename;
	uint32_t	frame;

	if (!assets->meta.sprite_frames)
		return (eno(E_FRAMES), false);
	assets->sprite = malloc(sizeof(t_frame) * assets->meta.sprite_frames);
	if (!assets->sprite)
		return (eno(E_MEM), false);
	filename = assets->meta.sprite_dir + ft_strlen(assets->meta.sprite_dir);
	frame = 0;
	while (frame < assets->meta.sprite_frames)
	{
		ft_bzero(filename, FRAME_SIZE);
		ft_itoa_buf(frame, filename);
		ft_strlcat(filename, ".png", FRAME_SIZE + 1);
		if (!load_asset(assets->meta.sprite_dir, &assets->sprite[frame++].tex))
			return (false);
		assets->sprite[frame - 1].next = &assets->sprite[frame];
	}
	assets->sprite[assets->meta.sprite_frames - 1].next = assets->sprite;
	return (true);
}

bool	load_assets(t_assets *assets, bool is_bonus)
{
	t_side	id;

	if (!init_font(&assets->font))
		return (false);
	id = A__SIZE_MAND;
	if (is_bonus)
		id = A__SIZE_BONUS;
	while (id-- != A__FIRST)
		if (!load_asset(assets->meta.path[id], &assets->tex[id]))
			return (free_assets(assets), false);
	if (is_bonus && !load_sprites(assets))
		return (free_assets(assets), false);
	return (true);
}
