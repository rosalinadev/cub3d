/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilinear_impl.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:33:32 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/20 20:02:12 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BILINEAR_IMPL_H
# define BILINEAR_IMPL_H

#include <stdint.h>

# include "types.h"

typedef struct s_bi
{
	uint32_t	i;
	uint32_t	j;
	uint8_t		s;
	t_vec2f		r;
	t_vec2f		l;
	t_vec2f		h;
	t_vec2f		w;
	float		a;
	float		b;
	float		c;
	float		d;
}	t_bi;

#endif
