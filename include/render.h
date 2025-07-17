/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 15:30:01 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/17 22:42:44 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "MLX42/MLX42.h"

# include "types.h"

typedef struct s_draw
{
	mlx_image_t		*disp;
	mlx_texture_t	*tex;
	int32_t			start;
	int32_t			end;
	uint32_t		x;
	uint32_t		h;
	t_vec2u			pos;
	uint32_t		*hbuf;
}	t_draw;

#endif
