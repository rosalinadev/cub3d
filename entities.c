/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 02:39:28 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/07 05:48:49 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	init_entities(t_map *map, t_coords c, unsigned int depth)
{
	while (c.y != map->height && map->c[c.y][c.x].t != C_PLAYER
									&& map->c[c.y][c.x].t != C_ENEMY)
		if (++c.x == map->width)
			c.x = (c.y++, 0);
	if (c.y == map->height)
		return (map->num_entities = depth,
			map->entities = ft_calloc(depth, sizeof(t_entity)), true);
	if (!init_entities(map, (t_coords){(c.x + 1) * (c.x + 1 != map->width),
			c.y + (c.x + 1 == map->width)}, depth + 1))
		return (false);
	if (map->c[c.y][c.x].t == C_PLAYER)
		map->player = &map->entities[depth];
	map->entities[depth] = (t_entity){.oc = c, .c = c, .t = map->c[c.y][c.x].t};
	return (true);
}

// TODO decide on collisions
void	set_map_weights(t_map *map, t_coords c, int depth)
{
	if (map->c[c.y][c.x].t == C_WALL
	|| (map->mem[c.y][c.x] && map->mem[c.y][c.x] <= depth))
		return ;
	map->mem[c.y][c.x] = depth;
	depth++;
	set_map_weights(map, (t_coords){c.x + 1, c.y}, depth);
	set_map_weights(map, (t_coords){c.x, c.y - 1}, depth);
	set_map_weights(map, (t_coords){c.x - 1, c.y}, depth);
	set_map_weights(map, (t_coords){c.x, c.y + 1}, depth);
}

int	iter_entities_variant(t_ctx *ctx,
		int (*f)(t_ctx *, t_entity *, unsigned int))
{
	unsigned int	i;
	unsigned char	variant;
	t_entity		*entity;

	i = -1;
	while (++i < ctx->map->num_entities)
	{
		entity = &ctx->map->entities[i];
		variant = -1;
		while (++variant < 32)
		{
			if ((ctx->assets[0][entity->t].has_variants && variant % 8 >= 4) \
			|| (!ctx->assets[0][entity->t].has_variants && variant % 8 >= 1))
				continue ;
			if (f(ctx, entity, variant) < 0)
				return (-1);
		}
	}
	return (0);
}

t_entity	*get_random_enemy(t_map *map)
{
	t_entity	*entity;

	entity = NULL;
	while (map->num_entities >= 2 && (entity == NULL || entity->t != C_ENEMY))
		entity = &map->entities[(unsigned int) round(mlx_get_time() * 10000) \
								% map->num_entities];
	return (entity);
}
