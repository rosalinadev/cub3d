/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 05:46:23 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/17 13:52:59 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "types.h"

void	vec2f_rotate(t_vec2f *u, float a)
{
	t_vec2f	v;

	v.x = cosf(a) * u->x - sinf(a) * u->y;
	v.y = sinf(a) * u->x + cosf(a) * u->y;
	*u = v;
}

t_vec2f	vec2f_mult(t_vec2f *u, t_vec2f *v)
{
	t_vec2f	w;

	w.x = u->x * v->x;
	w.y = u->y * v->y;
	return (w);
}

t_vec2f	vec2f_add(t_vec2f *u, t_vec2f *v)
{
	t_vec2f	w;

	w.x = u->x + v->x;
	w.y = u->y + v->y;
	return (w);
}

t_vec2f	vec2f_sub(t_vec2f *u, t_vec2f *v)
{
	t_vec2f	w;

	w.x = u->x - v->x;
	w.y = u->y - v->y;
	return (w);
}
