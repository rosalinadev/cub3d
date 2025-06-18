/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:52:15 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/17 05:56:08 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "types.h"

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
