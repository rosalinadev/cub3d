/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:20:44 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/18 15:00:54 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

#include "defaults.h"
#include "player.h"

void	player_respawn(t_player *player, t_map *map)
{
	static bool	init_done;

	if (!init_done)
		player->fov = FOV;
	player->pos = (t_vec2f){map->spawn_pos.x + 0.5, map->spawn_pos.y + 0.5};
	player->dir = map->spawn_facing;
	player_set_fov(player, 0);
}

// set fov to 0 to keep previous fov
void	player_set_fov(t_player *player, float fov)
{
	float	s;

	if (fov)
		player->fov = fov;
	s = tanf(player->fov * M_PI / 180.0 / 2.0);
	player->cam = (t_vec2f){-player->dir.y * s, player->dir.x * s};
}
