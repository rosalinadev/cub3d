/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:54:18 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/20 22:35:33 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
