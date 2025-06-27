/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:19:14 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/27 22:38:14 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "map.h"
# include "types.h"

typedef struct s_player
{
	t_vec2f	pos;
	t_vec2f	dir;
	bool	noclip;
	float	fov;
	// half of fov
	t_vec2f	cam;
}	t_player;

// player.c
void	player_respawn(t_player *player, t_map *map);
void	player_set_fov(t_player *player, float fov);

#endif
