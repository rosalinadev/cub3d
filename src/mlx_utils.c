/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:54:18 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/20 20:12:01 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"

#include "bilinear_impl.h"

void	mlx_clear_image(mlx_image_t *img)
{
	uint32_t	*pixels;
	size_t		i;

	pixels = (uint32_t *)img->pixels;
	i = img->width * img->height;
	while (i)
		pixels[--i] = 0;
}

mlx_texture_t	*mlx_new_texture(uint32_t width, uint32_t height)
{
	mlx_texture_t	*tex;
	uint32_t		*pixels;
	size_t			i;

	if (!width || !height)
		return (NULL);
	tex = malloc(sizeof(mlx_texture_t));
	if (!tex)
		return (NULL);
	*tex = (mlx_texture_t){.width = width, .height = height,
		.bytes_per_pixel = 4, .pixels = malloc(width * height * 4)};
	if (!tex->pixels)
		return (free(tex), NULL);
	pixels = (uint32_t *)tex->pixels;
	i = width * height;
	while (i)
		pixels[--i] = 0;
	return (tex);
}

// https://gist.github.com/folkertdev/6b930c7a7856e36dcad0a72a03e66716
static inline void	bilinear_impl(t_bi *bi,
		mlx_texture_t *in, mlx_texture_t *out)
{
	bi->l.x = floorf(bi->r.x * (float)bi->j);
	bi->l.y = floorf(bi->r.y * (float)bi->i);
	bi->h.x = ceilf(bi->r.x * (float)bi->j);
	bi->h.y = ceilf(bi->r.y * (float)bi->i);
	bi->w.x = (bi->r.x * (float)bi->j) - bi->l.x;
	bi->w.y = (bi->r.y * (float)bi->i) - bi->l.y;
	bi->a = in->pixels[((int)bi->l.y * in->width + (int)bi->l.x) * 4 + bi->s];
	bi->b = in->pixels[((int)bi->l.y * in->width + (int)bi->h.x) * 4 + bi->s];
	bi->c = in->pixels[((int)bi->h.y * in->width + (int)bi->l.x) * 4 + bi->s];
	bi->d = in->pixels[((int)bi->h.y * in->width + (int)bi->h.x) * 4 + bi->s];
	out->pixels[(bi->i * out->width + bi->j) * 4 + bi->s]
		= (bi->a * (1.0 - bi->w .x) * (1.0 - bi->w.y)
			+ bi->b * bi->w.x * (1.0 - bi->w.y)
			+ bi->c * bi->w.y * (1.0 - bi->w.x)
			+ bi->d * bi->w.x * bi->w.y);
}

void	mlx_scale_texture(mlx_texture_t *in, mlx_texture_t *out)
{
	t_bi	bi;

	bi = (t_bi){};
	bi.r.x = ((float)in->width - 1.0) / ((float)out->width - 1.0);
	bi.r.y = ((float)in->height - 1.0) / ((float)out->height - 1.0);
	while (bi.i < out->height)
	{
		bi.j = 0;
		while (bi.j < out->width)
		{
			bi.s = 0;
			while (bi.s < 4)
			{
				bilinear_impl(&bi, in, out);
				bi.s++;
			}
			bi.j++;
		}
		bi.i++;
	}
}
