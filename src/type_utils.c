/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:15 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/20 13:02:33 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "types.h"

// idk why i added this when every side has a different texture
t_col	color_mult(t_col lhs, t_col rhs)
{
	return ((t_col){.rgba = {
			roundf((float)lhs.rgba[0] * rhs.rgba[0] / 0xFF),
			roundf((float)lhs.rgba[1] * rhs.rgba[1] / 0xFF),
			roundf((float)lhs.rgba[2] * rhs.rgba[2] / 0xFF),
			roundf((float)lhs.rgba[3] * rhs.rgba[3] / 0xFF)
		}});
}

t_vec2	vec2f_floor(t_vec2f vec)
{
	return ((t_vec2){floorf(vec.x), floorf(vec.y)});
}

t_vec2	vec2_u2s(t_vec2u vec)
{
	return ((t_vec2){vec.x, vec.y});
}

t_vec2u	vec2_s2u(t_vec2 vec)
{
	return ((t_vec2u){vec.x, vec.y});
}
