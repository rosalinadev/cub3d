/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 05:46:23 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/18 06:48:31 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "types.h"

void	vec2f_rotate(t_vec2f *u, float a)
{
	t_vec2f	v;
	t_vec2f	tmp;

	tmp.x = cosf(a);
	tmp.y = sinf(a);
	v.x = tmp.x * u->x - tmp.y * u->y;
	v.y = tmp.y * u->x + tmp.x * u->y;
	*u = v;
}

t_vec2f	vec2f_scale(t_vec2f *u, float s)
{
	t_vec2f	v;

	v.x = u->x * s;
	v.y = u->y * s;
	return (v);
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
