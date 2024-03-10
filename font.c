/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:35:51 by rvandepu          #+#    #+#             */
/*   Updated: 2024/03/10 15:21:32 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define FHEIGHT 16

static inline int	get_char_width_skip(mlx_texture_t *img, t_coords *c)
{
	int	w;

	while (c->x < img->width && c->y < img->height
		&& !img->pixels[(c->y * img->width + c->x) * 4 + 3])
		if (++c->x == img->width)
			c->x = (c->y += FHEIGHT + 1, 0);
	w = 0;
	while (c->x < img->width && c->y < img->height
		&& img->pixels[(c->y * img->width + c->x) * 4 + 3])
		if (w++, ++c->x == img->width)
			c->x = (c->y += FHEIGHT + 1, 0);
	if (w)
		w += 2;
	while (c->x < img->width && c->y < img->height
		&& !img->pixels[(c->y * img->width + c->x) * 4 + 3])
		if (++c->x == img->width)
			c->x = (c->y += FHEIGHT + 1, 0);
	return (w);
}

bool	init_font(t_ctx *ctx)
{
	t_coords	p;
	char		c;

	ctx->font.img = mlx_load_png("hall-fetica-bold.png");
	if (ctx->font.img == NULL)
		return (g_eno = E_FONT, false);
	ctx->counter = mlx_new_image(ctx->mlx, ctx->width, ctx->height);
	ctx->gametext = mlx_new_image(ctx->mlx, ctx->width, ctx->height);
	if (ctx->counter == NULL || ctx->gametext == NULL
		|| mlx_image_to_window(ctx->mlx, ctx->counter, 0, 0) < 0
		|| mlx_image_to_window(ctx->mlx, ctx->gametext, 0, 0) < 0)
		return (g_eno = E_IMG, mlx_delete_texture(ctx->font.img), false);
	ctx->font.sc = 1;
	if (ctx->map->width >= 5)
		ctx->font.sc = 2;
	if (ctx->map->width >= 8)
		ctx->font.sc = 3;
	p = (t_coords){0, FHEIGHT};
	c = ' ';
	while (c <= '~')
		ctx->font.meta[c++ - ' '] = (t_char){(t_coords){p.x, p.y - FHEIGHT}, \
			{get_char_width_skip(ctx->font.img, &p), FHEIGHT}};
	return (true);
}

static inline void	draw_char(mlx_image_t *i, t_font *f, char c, t_coords p)
{
	t_char			*m;
	t_coords		o;

	if (c < ' ' || '~' < c)
		return ;
	m = &f->meta[c - ' '];
	o = (t_coords){0, 0};
	while (o.y < m->s.y * f->sc)
	{
		if (f->img->pixels[((m->p.y + o.y / f->sc)
					* f->img->width + m->p.x + o.x / f->sc) * 4 + 3])
		{
			i->pixels[((p.y + o.y) * i->width + p.x + o.x) * 4] = f->img-> \
pixels[((m->p.y + o.y / f->sc) * f->img->width + m->p.x + o.x / f->sc) * 4];
			i->pixels[((p.y + o.y) * i->width + p.x + o.x) * 4 + 1] = f->img-> \
pixels[((m->p.y + o.y / f->sc) * f->img->width + m->p.x + o.x / f->sc) * 4 + 1];
			i->pixels[((p.y + o.y) * i->width + p.x + o.x) * 4 + 2] = f->img-> \
pixels[((m->p.y + o.y / f->sc) * f->img->width + m->p.x + o.x / f->sc) * 4 + 2];
			i->pixels[((p.y + o.y) * i->width + p.x + o.x) * 4 + 3] = f->img-> \
pixels[((m->p.y + o.y / f->sc) * f->img->width + m->p.x + o.x / f->sc) * 4 + 3];
		}
		if (++o.x == m->s.x * f->sc)
			o.x = (o.y++, 0);
	}
}

t_coords	str_size(t_font *font, const char *str)
{
	unsigned int	width;
	unsigned int	i;

	width = 0;
	i = 0;
	while (' ' <= str[i] && str[i] <= '~')
		width += font->meta[str[i++] - ' '].s.x;
	if (!i || str[i])
		return ((t_coords){0, 0});
	else
		return ((t_coords){width * font->sc, FHEIGHT * font->sc});
}

bool	draw_str(mlx_image_t *img, t_font *font, const char *str, t_coords pos)
{
	unsigned int	i;
	t_coords		c;

	c = str_size(font, str);
	if (pos.x + c.x >= img->width || pos.y + c.y >= img->height)
		return (false);
	c = pos;
	i = 0;
	while (' ' <= str[i] && str[i] <= '~')
	{
		draw_char(img, font, str[i], c);
		c.x += font->meta[str[i] - ' '].s.x * font->sc;
		i++;
	}
	if (str[i])
		return (false);
	return (true);
}
