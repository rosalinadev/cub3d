/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:58 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/01 22:40:22 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_to(t_map *map, t_entity *entity, t_coords nc)
{
	entity->oc = entity->c;
	if (entity->c.x == nc.x && entity->c.y == nc.y)
		return ;
	if (entity->c.x < nc.x)
		entity->d = F_WEST;
	else if (nc.y < entity->c.y)
		entity->d = F_NORTH;
	else if (nc.x < entity->c.x)
		entity->d = F_EAST;
	else if (entity->c.y < nc.y)
		entity->d = F_SOUTH;
	if (map->c[nc.y][nc.x].t == C_WALL)
		return ;
	entity->c = nc;
	map->c[entity->oc.y][entity->oc.x].t = C_EMPTY;
	map->c[entity->c.y][entity->c.x].t = entity->t;
	return ;
}

// TODO count moves
void	move_player(t_ctx *ctx)
{
	t_entity	*player;

	player = ctx->map->player;
	if (ctx->flags & (1 << P_RIGHT | 1 << H_RIGHT))
		move_to(ctx->map, player, (t_coords){player->c.x + 1, player->c.y});
	else if (ctx->flags & (1 << P_UP | 1 << H_UP))
		move_to(ctx->map, player, (t_coords){player->c.x, player->c.y - 1});
	else if (ctx->flags & (1 << P_LEFT | 1 << H_LEFT))
		move_to(ctx->map, player, (t_coords){player->c.x - 1, player->c.y});
	else if (ctx->flags & (1 << P_DOWN | 1 << H_DOWN))
		move_to(ctx->map, player, (t_coords){player->c.x, player->c.y + 1});
}

// TODO move random enemies
/*void	move_enemies(t_ctx *ctx)
{
	int			i;
	t_entity	*enemy;

	if (ctx->map->num_entities < 2)
		return ;

	enemy = get_random_enemy(ctx->map);
}*/
