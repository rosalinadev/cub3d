/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 00:28:44 by rvandepu          #+#    #+#             */
/*   Updated: 2024/02/03 21:13:17 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*static void	free_assets(t_ctx *ctx)
{
	int			frame;
	t_cell_type	type;
	int			variant;

	frame = 3;
	while (frame--)
	{
		type = 0;
		while (type++ < C_MAXTYPE)
		{
			variant = 16;
			while (variant--)
				if (ctx->assets[frame][type].img[variant])
					mlx_delete_image(ctx->mlx,
						ctx->assets[frame][type].img[variant]);
		}
	}
	ft_bzero(ctx->assets, sizeof(t_asset[3][C_MAXTYPE]));
}*/

static const t_asset	g_asset_meta[C_MAXTYPE] = {\
	[C_WALL] = {{{"wall", {0x293141FF}}}, true}, \
	[C_COLLECTIBLE] = {{{"key", {0xede285FF}}}, false}, \
	[C_EXIT] = {{{"door", {0xe5533bFF}}}, false}, \
};

static int	get_path(char path[100], t_cell_type type, int variant, int frame)
{
	char	*tmp;

	ft_bzero(path, 100);
	ft_strlcat(path, "sprites/", 100);
	ft_strlcat(path, g_asset_meta[type].s_meta.name, 100);
	ft_strlcat(path, "_", 100);
	tmp = ft_itoa(variant);
	if (tmp == NULL)
		return (-1);
	ft_strlcat(path, tmp, 100);
	free(tmp);
	ft_strlcat(path, "_", 100);
	tmp = ft_itoa(frame);
	if (tmp == NULL)
		return (-1);
	ft_strlcat(path, tmp, 100);
	free(tmp);
	ft_strlcat(path, ".png", 100);
	return (0);
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

static int	load_asset(t_ctx *ctx, t_cell_type type, int frame)
{
	char			path[100];
	int				variant;
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	variant = 1;
	if (g_asset_meta[type].has_variants)
		variant = 16;
	ctx->assets[frame][type].has_variants = g_asset_meta[type].has_variants;
	while (variant--)
	{
		if (get_path(path, type, variant, frame + 1) < 0)
			return (-1);
		texture = mlx_load_png(path);
		if (texture == NULL)
			return (-1);
		recolor_texture(texture, g_asset_meta[type].s_meta.color);
		image = mlx_texture_to_image(ctx->mlx, texture);
		mlx_resize_image(image, image->width * 2, image->height * 2);
		ctx->assets[frame][type].img[variant] = image;
		mlx_delete_texture(texture);
		if (!ctx->assets[frame][type].img[variant])
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
		if (load_asset(ctx, C_WALL, frame) < 0
			|| load_asset(ctx, C_COLLECTIBLE, frame) < 0
			|| load_asset(ctx, C_EXIT, frame) < 0)
			return (-1);
	}
	return (0);
}
