/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:26:09 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/17 08:13:09 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include "MLX42/MLX42.h"
# include "types.h"

typedef struct s_char
{
	t_vec2u	p;
	t_vec2u	s;
}	t_char;

typedef struct s_font
{
	mlx_texture_t	*tex;
	t_char			meta['~' - ' ' + 1]; // ascii size
	unsigned char	sc;
}	t_font;

// font.c
bool	init_font(t_font *font);
t_vec2u	str_size(t_font *font, const char *str);
bool	draw_str(mlx_image_t *img, t_font *font, const char *str, t_vec2u pos);

#endif
