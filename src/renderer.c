/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 07:26:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/18 14:44:25 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "MLX42/MLX42.h"
#include "libft.h"

#include "map.h"
#include "player.h"
#include "raycast.h"

static const uint32_t	g_side_to_color[4] = {
	0xFF0000FF,
	0x00FF00FF,
	0x0000FFFF,
	0xFFFF00FF
};

static void	draw_slice(mlx_image_t *screen,
		uint32_t x, t_raycast *ray, int height)
{
	int	start;
	int	end;

	start = ft_max(2, ((int32_t)screen->height - height) / 2, 0);
	end = ft_min(2, (screen->height + height) / 2 + 1, screen->height);
	while (start < end)
		mlx_put_pixel(screen, x, start++, g_side_to_color[ray->hit_side]);
}

static void	render_slices(mlx_image_t *screen, t_map *map, t_player *player)
{
	t_raycast	ray;
	uint32_t	x;
	int			height;

	ray = (t_raycast){.map = map, .player = player};
	x = 0;
	while (x < screen->width)
	{
		ray.dir = vec2f_add(player->dir, vec2f_scale(
					&player->cam, 2.0 * x / screen->width - 1));
		cast_ray(&ray);
		if (ray.hit)
		{
			height = screen->width / ray.dist / (hypotf(player->cam.x,
						player->cam.y) * 2);
			draw_slice(screen, x, &ray, height);
		}
		x++;
	}
}

void	render_screen(mlx_image_t *screen, t_map *map, t_player *player)
{
	ft_bzero(screen->pixels, screen->width * screen->height * 4);
	render_slices(screen, map, player);
}
