/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:09:28 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/22 12:06:57 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdint.h>

# include "MLX42/MLX42.h"

typedef uint32_t	t_kb;
typedef enum e_kb_bit
{
	H_FORWARDS = 1,
	H_BACKWARDS,
	H_LEFT,
	H_RIGHT,
	H_SPRINT,
	H_LOOKLEFT,
	H_LOOKRIGHT,
	P_QUIT,
	P_MINIMAP,
	P_FULLSCREEN,
}	t_kb_bit;

void	hook_key(mlx_key_data_t keydata, void *param);

#endif
