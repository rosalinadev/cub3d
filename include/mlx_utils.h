/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:53:52 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/09 12:53:58 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "MLX42/MLX42.h"

# include "types.h"

void	mlx_clear_image(mlx_image_t *img);
void	draw_background(mlx_image_t	*img, uint32_t ceil, uint32_t floor);
bool	get_win_size(t_vec2 *size, bool fullscreen);
void	set_pixel(t_col *pixel, t_col value);
double	get_time(void);

#endif
