/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:58 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/07 05:48:51 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// TODO choose collision, kill player?
static bool	move_to(t_map *map, t_entity *entity, t_coords nc)
{
	entity->oc = entity->c;
	if (entity->c.x == nc.x && entity->c.y == nc.y)
		return (false);
	if (entity->c.x < nc.x)
		entity->d = F_WEST;
	else if (nc.y < entity->c.y)
		entity->d = F_NORTH;
	else if (nc.x < entity->c.x)
		entity->d = F_EAST;
	else if (entity->c.y < nc.y)
		entity->d = F_SOUTH;
	if (map->c[nc.y][nc.x].t == C_WALL || map->c[nc.y][nc.x].t == C_ENEMY
		|| map->c[nc.y][nc.x].t == C_PLAYER)
		return (false);
	entity->lm = mlx_get_time();
	entity->c = nc;
	map->c[entity->oc.y][entity->oc.x].t = C_EMPTY;
	map->c[entity->c.y][entity->c.x].t = entity->t;
	return (true);
}

bool	move_player(t_map *map, t_flags flags)
{
	t_entity	*player;

	player = map->player;
	if (ft_bit_check(flags, H_RIGHT))
		return (move_to(map, player, (t_coords){player->c.x + 1, player->c.y}));
	else if (ft_bit_check(flags, H_UP))
		return (move_to(map, player, (t_coords){player->c.x, player->c.y - 1}));
	else if (ft_bit_check(flags, H_LEFT))
		return (move_to(map, player, (t_coords){player->c.x - 1, player->c.y}));
	else if (ft_bit_check(flags, H_DOWN))
		return (move_to(map, player, (t_coords){player->c.x, player->c.y + 1}));
	return (false);
}

void	move_enemy(t_map *map, t_entity *e)
{
	int	r;
	int	u;
	int	l;
	int	d;

	r = map->mem[e->c.y][e->c.x + 1];
	u = map->mem[e->c.y - 1][e->c.x];
	l = map->mem[e->c.y][e->c.x - 1];
	d = map->mem[e->c.y + 1][e->c.x];
	if (r && (r <= u || !u) && (r <= l || !l) && (r <= d || !d))
		move_to(map, e, (t_coords){e->c.x + 1, e->c.y});
	else if (u && (u <= r || !r) && (u <= l || !l) && (u <= d || !d))
		move_to(map, e, (t_coords){e->c.x, e->c.y - 1});
	else if (l && (l <= r || !r) && (l <= u || !u) && (l <= d || !d))
		move_to(map, e, (t_coords){e->c.x - 1, e->c.y});
	else if (d && (d <= r || !r) && (d <= u || !u) && (d <= l || !l))
		move_to(map, e, (t_coords){e->c.x, e->c.y + 1});
	e->m = true;
}

void	move_enemies(t_map *map)
{
	unsigned int	i;
	t_entity		*enemy;

	if (map->num_entities < 2)
		return ;
	i = 0;
	while (i < map->num_entities / 2)
	{
		enemy = get_random_enemy(map);
		if (!enemy || enemy->m)
			continue ;
		move_enemy(map, enemy);
		i++;
	}
}
