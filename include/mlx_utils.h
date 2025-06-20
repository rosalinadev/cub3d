/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:53:52 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/20 14:59:48 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "MLX42/MLX42.h"

void			mlx_clear_image(mlx_image_t *img);
mlx_texture_t	*mlx_new_texture(uint32_t width, uint32_t height);
void			mlx_scale_texture(mlx_texture_t *in, mlx_texture_t *out);

#endif
