/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:54:18 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/09 12:52:12 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"

#include "defaults.h"
#include "error.h"
#include "mlx_utils.h"

void	mlx_clear_image(mlx_image_t *img)
{
	uint32_t	*pixels;
	size_t		i;

	pixels = (uint32_t *)img->pixels;
	i = img->width * img->height;
	while (i)
		pixels[--i] = 0;
}

void	draw_background(mlx_image_t	*img, uint32_t ceil, uint32_t floor)
{
	uint32_t	*pixels;
	size_t		i;

	pixels = (uint32_t *)img->pixels;
	i = img->width * img->height / 2;
	while (i)
		pixels[--i] = ceil;
	pixels += img->width * img->height / 2;
	i = img->width * (img->height / 2 + img->height % 2);
	while (i)
		pixels[--i] = floor;
}

bool	get_win_size(t_vec2 *size, bool fullscreen)
{
	mlx_t	*mlx;

	size->x = WIDTH;
	size->y = HEIGHT;
	if (fullscreen)
	{
		mlx_set_setting(MLX_FULLSCREEN, false);
		mlx_set_setting(MLX_HEADLESS, true);
		mlx = mlx_init(size->x, size->y, NAME, false);
		if (!mlx)
			return (eno(E_MLX), false);
		mlx_get_monitor_size(0, &size->x, &size->y);
		mlx_terminate(mlx);
		mlx_set_setting(MLX_HEADLESS, false);
	}
	return (true);
}

void	set_pixel(t_col *pixel, t_col value)
{
	if (value.a == 0xFF)
		pixel->col = value.col;
	else if (value.a)
	{
		pixel->r = ((0xFF - value.a) * pixel->r + value.a * value.r) / 0xFF;
		pixel->g = ((0xFF - value.a) * pixel->g + value.a * value.g) / 0xFF;
		pixel->b = ((0xFF - value.a) * pixel->b + value.a * value.b) / 0xFF;
		pixel->a = 0xFF;
	}
}

double	get_time(void)
{
	static double	offset;
	static double	last_time;
	double			time;

	time = mlx_get_time();
	if (time + offset < last_time)
		offset = last_time;
	last_time = time + offset;
	return (last_time);
}
