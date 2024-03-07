/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:59:35 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/07 10:50:08 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static inline void	set_frame(t_asset *asset, bool enabled)
{
	unsigned char	variant;

	variant = -1;
	while (++variant < 32)
	{
		if ((asset->is_entity && asset->has_variants && variant % 8 >= 4) \
		|| (asset->is_entity && !asset->has_variants && variant % 8 >= 1) \
		|| (!asset->is_entity && asset->has_variants && variant >= 16) \
		|| (!asset->is_entity && !asset->has_variants && variant >= 1))
			continue ;
		if (asset->img[variant])
			asset->img[variant]->enabled = enabled;
	}
}

void	update_frame(t_ctx *ctx, double time)
{
	static double			last_time = 0;
	static unsigned char	frame = 0;
	unsigned char			i;
	unsigned char			j;

	if (!last_time)
		return ((void)(last_time = time));
	if (time - last_time < FRAME_TIME)
		return ;
	if (++frame == 3)
		frame = 0;
	i = 0;
	while (++i < C_MAXTYPE)
	{
		j = 3;
		while (j--)
			set_frame(&ctx->assets[j][i], j == frame);
	}
	last_time = time;
}

int	update_entity_variant(t_ctx *ctx, t_entity *entity, unsigned int variant)
{
	unsigned char	frame;

	if (!variant && ctx->assets[0][entity->t].has_variants
		&& (entity->oc.x != entity->c.x || entity->oc.y != entity->c.y)
		&& ++entity->f == 4)
		entity->f = 0;
	entity->m = false;
	frame = -1;
	while (++frame < 3)
		ctx->assets[frame][entity->t].img[variant]->instances[entity->i[frame] \
			[variant]].enabled = entity->d * 8 + entity->f == variant;
	return (0);
}

void	render_entities(t_ctx *ctx, double curr)
{
	unsigned int	i;
	unsigned int	f;
	unsigned char	v;
	t_entity		*e;

	i = -1;
	while (++i < ctx->map->num_entities)
	{
		e = &ctx->map->entities[i];
		v = e->d * 8 + e->f;
		if (curr - e->lm > ANIM_TIME)
			e->lm = curr - ANIM_TIME;
		f = -1;
		while (++f < 3)
		{
			ctx->assets[f][e->t].img[v]->instances[e->i[f][v]].x = round(CSIZE \
			* (e->oc.x + (curr - e->lm) / ANIM_TIME * (int)(e->c.x - e->oc.x)));
			ctx->assets[f][e->t].img[v]->instances[e->i[f][v]].y = round(CSIZE \
			* (e->oc.y + (curr - e->lm) / ANIM_TIME * (int)(e->c.y - e->oc.y)));
		}
	}
}
