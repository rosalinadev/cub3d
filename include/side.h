/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:55:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/21 05:49:49 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIDE_H
# define SIDE_H

// also for asset IDs
typedef enum e_side
{
	SIDE__FIRST = 0,
	SIDE_W = SIDE__FIRST,
	SIDE_E,
	SIDE_N,
	SIDE_S,
	SIDE__SIZE,
	// same order
	A__FIRST = SIDE__FIRST,
	A_W = A__FIRST,
	A_E,
	A_N,
	A_S,
	A_DOOR,
	A__SIZE
}	t_side;

#endif
