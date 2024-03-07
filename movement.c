/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:58 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/07 17:47:07 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_events(t_ctx *ctx, t_entity *e)
{
	unsigned char	frame;
	t_map			*map;

	map = ctx->map;
	if (e->t == C_ENEMY && map->c[e->c.y][e->c.x].t == C_PLAYER)
		map->gamestate = G_LOST;
	if (e->t == C_PLAYER && map->c[e->c.y][e->c.x].t == C_COLLECTIBLE)
	{
		frame = -1;
		while (++frame < 3)
			ctx->assets[frame][C_COLLECTIBLE].img[0]
				->instances[map->c[e->c.y][e->c.x].i[frame]].enabled = false;
		map->collectibles--;
		if (map->collectibles)
			ft_printf("Collectible get! %d left.\n", map->collectibles);
		else
			ft_printf("You got all collectibles, go to the exit to finish!\n");
		map->c[e->c.y][e->c.x].t = C_EMPTY;
	}
	if (e->t == C_PLAYER && map->c[e->c.y][e->c.x].t == C_EXIT
			&& !map->collectibles)
		map->gamestate = G_WON;
}

static bool	move_to(t_ctx *c, t_entity *entity, t_coords nc)
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
	if (c->map->c[nc.y][nc.x].t == C_WALL || c->map->c[nc.y][nc.x].t == C_ENEMY)
		return (false);
	entity->lm = mlx_get_time();
	entity->c = nc;
	move_events(c, entity);
	if (c->map->c[entity->oc.y][entity->oc.x].t == entity->t)
		c->map->c[entity->oc.y][entity->oc.x].t = C_EMPTY;
	if (c->map->c[entity->c.y][entity->c.x].t == C_EMPTY)
		c->map->c[entity->c.y][entity->c.x].t = entity->t;
	return (true);
}

bool	move_player(t_ctx *ctx, t_flags flags)
{
	t_entity	*player;

	player = ctx->map->player;
	if (ft_bit_check(flags, H_RIGHT))
		return (move_to(ctx, player, (t_coords){player->c.x + 1, player->c.y}));
	else if (ft_bit_check(flags, H_UP))
		return (move_to(ctx, player, (t_coords){player->c.x, player->c.y - 1}));
	else if (ft_bit_check(flags, H_LEFT))
		return (move_to(ctx, player, (t_coords){player->c.x - 1, player->c.y}));
	else if (ft_bit_check(flags, H_DOWN))
		return (move_to(ctx, player, (t_coords){player->c.x, player->c.y + 1}));
	return (false);
}

static inline void	move_enemy(t_ctx *ctx, t_entity *e)
{
	int	r;
	int	u;
	int	l;
	int	d;

	r = ctx->map->mem[e->c.y][e->c.x + 1];
	u = ctx->map->mem[e->c.y - 1][e->c.x];
	l = ctx->map->mem[e->c.y][e->c.x - 1];
	d = ctx->map->mem[e->c.y + 1][e->c.x];
	if (r && (r <= u || !u) && (r <= l || !l) && (r <= d || !d))
		move_to(ctx, e, (t_coords){e->c.x + 1, e->c.y});
	else if (u && (u <= r || !r) && (u <= l || !l) && (u <= d || !d))
		move_to(ctx, e, (t_coords){e->c.x, e->c.y - 1});
	else if (l && (l <= r || !r) && (l <= u || !u) && (l <= d || !d))
		move_to(ctx, e, (t_coords){e->c.x - 1, e->c.y});
	else if (d && (d <= r || !r) && (d <= u || !u) && (d <= l || !l))
		move_to(ctx, e, (t_coords){e->c.x, e->c.y + 1});
	e->m = true;
}

void	move_enemies(t_ctx *ctx)
{
	unsigned int	i;
	t_entity		*enemy;

	if (ctx->map->num_entities < 2)
		return ;
	i = 0;
	while (i < ctx->map->num_entities / 2)
	{
		enemy = get_random_enemy(ctx->map);
		if (!enemy || enemy->m)
			continue ;
		move_enemy(ctx, enemy);
		i++;
	}
}
