/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 07:27:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/04/08 19:18:04 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>

typedef union u_color
{
	uint32_t	col;
	uint8_t		rgba[4];
}	t_col;

typedef struct s_vec2u
{
	uint32_t	x;
	uint32_t	y;
}	t_vec2u;

typedef struct s_vec2
{
	int32_t	x;
	int32_t	y;
}	t_vec2;

typedef struct s_vec2f
{
	float	x;
	float	y;
}	t_vec2f;

typedef struct s_vec3f
{
	float	x;
	float	y;
	float	z;
}	t_vec3f;

// type_utils.c
t_vec2	vec2_floor(t_vec2f vec);
t_vec2	vec2_u2s(t_vec2u vec);
t_vec2u	vec2_s2u(t_vec2 vec);

#endif
