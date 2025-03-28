/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:28:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/03/28 02:49:46 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const t_asset	g_asset_meta[C_MAXTYPE] = {\
	[C_WALL] = {{{"wall", {0x293141FF}}}, false, true}, \
	[C_COLLECTIBLE] = {{{"boba", {0xC29E46FF}}}, false, false}, \
	[C_EXIT] = {{{"door", {0xE5533BFF}}}, false, false}, \
	[C_PLAYER] = {{{"baba", {0xFFFFFFFF}}}, true, true}, \
	[C_ENEMY] = {{{"it", {0x82261CFF}}}, true, true}, \
};

static void	get_path(char path[100], t_cell_type type, int variant, int frame)
{
	char	num[11];

	ft_bzero(path, 100);
	ft_strlcat(path, "sprites/", 100);
	ft_strlcat(path, g_asset_meta[type].s_meta.name, 100);
	ft_strlcat(path, "_", 100);
	putnbr_buf(variant, num);
	ft_strlcat(path, num, 100);
	ft_strlcat(path, "_", 100);
	putnbr_buf(frame, num);
	ft_strlcat(path, num, 100);
	ft_strlcat(path, ".png", 100);
}

static void	recolor_texture(mlx_texture_t *tex, t_col col)
{
	t_coords	c;

	c.y = 0;
	while (c.y < tex->height)
	{
		c.x = 0;
		while (c.x < tex->width)
		{
			if (tex->pixels[(c.y * tex->height + c.x) * 4 + 3])
			{
				tex->pixels[(c.y * tex->height + c.x) * 4 + 0] = roundf(\
	(float)tex->pixels[(c.y * tex->height + c.x) * 4 + 0] * col.rgba[3] / 0xFF);
				tex->pixels[(c.y * tex->height + c.x) * 4 + 1] = roundf(\
	(float)tex->pixels[(c.y * tex->height + c.x) * 4 + 1] * col.rgba[2] / 0xFF);
				tex->pixels[(c.y * tex->height + c.x) * 4 + 2] = roundf(\
	(float)tex->pixels[(c.y * tex->height + c.x) * 4 + 2] * col.rgba[1] / 0xFF);
				tex->pixels[(c.y * tex->height + c.x) * 4 + 3] = roundf(\
	(float)tex->pixels[(c.y * tex->height + c.x) * 4 + 3] * col.rgba[0] / 0xFF);
			}
			c.x++;
		}
		c.y++;
	}
}

static int	load_variant(t_ctx *ctx, t_cell_type type, int frame, int variant)
{
	char			path[100];
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	get_path(path, type, variant, frame + 1);
	texture = mlx_load_png(path);
	if (texture == NULL)
		return (g_eno = E_PNG, -1);
	recolor_texture(texture, g_asset_meta[type].s_meta.color);
	image = mlx_texture_to_image(ctx->mlx, texture);
	mlx_delete_texture(texture);
	if (image == NULL)
		return (g_eno = E_MEM, -1);
	if (!mlx_resize_image(image, CSIZE, CSIZE))
		return (g_eno = E_MEM, -1);
	ctx->assets[frame][type].img[variant] = image;
	return (0);
}

static int	load_asset(t_ctx *ctx, t_cell_type type, int frame)
{
	int				variant;
	bool			is_entity;
	bool			has_variants;

	is_entity = g_asset_meta[type].is_entity;
	has_variants = g_asset_meta[type].has_variants;
	ctx->assets[frame][type].is_entity = is_entity;
	ctx->assets[frame][type].has_variants = has_variants;
	variant = -1;
	while (++variant < 32)
	{
		if ((is_entity && has_variants && variant % 8 >= 4) \
		|| (is_entity && !has_variants && variant % 8 >= 1) \
		|| (!is_entity && has_variants && variant >= 16) \
		|| (!is_entity && !has_variants && variant >= 1))
			continue ;
		if (load_variant(ctx, type, frame, variant) < 0)
			return (-1);
	}
	return (0);
}

int	load_assets(t_ctx *ctx)
{
	int	frame;

	frame = 3;
	while (frame--)
	{
		if (load_asset(ctx, C_WALL, frame) < 0 \
		|| load_asset(ctx, C_COLLECTIBLE, frame) < 0 \
		|| load_asset(ctx, C_EXIT, frame) < 0 \
		|| load_asset(ctx, C_PLAYER, frame) < 0 \
		|| load_asset(ctx, C_ENEMY, frame) < 0)
			return (-1);
	}
	return (0);
}
