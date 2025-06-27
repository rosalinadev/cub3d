/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 00:35:51 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/27 22:20:42 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "defaults.h"
#include "error.h"
#include "font.h"

#define FHEIGHT 16

static inline int	get_char_width_skip(mlx_texture_t *img, t_vec2u *c)
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

bool	init_font(t_font *font)
{
	t_vec2u	p;
	char	c;

	font->tex = mlx_load_png(FONT_PATH);
	if (font->tex == NULL)
		return (eno(E_FONT), false);
	font->sc = FONT_SCALE;
	p = (t_vec2u){0, FHEIGHT};
	c = ' ';
	while (c <= '~')
		font->meta[c++ - ' '] = ((t_char){
			{p.x, p.y - FHEIGHT},
			{get_char_width_skip(font->tex, &p), FHEIGHT}
			});
	return (true);
}

static inline void	draw_char(mlx_image_t *i, t_font *f, char c, t_vec2u p)
{
	t_char		*m;
	t_vec2u		o;
	uint32_t	pixel;

	if (c < ' ' || '~' < c)
		return ;
	m = &f->meta[c - ' '];
	o = (t_vec2u){0, 0};
	while (o.y < m->s.y * f->sc)
	{
		pixel = ((uint32_t *)f->tex->pixels)[(m->p.y + o.y / f->sc)
			* f->tex->width + m->p.x + o.x / f->sc];
		if (pixel & 0xFF000000)
			((uint32_t *)i->pixels)[(p.y + o.y) * i->width + p.x + o.x] = pixel;
		if (++o.x == m->s.x * f->sc)
			o.x = (o.y++, 0);
	}
}

t_vec2u	str_size(t_font *font, const char *str)
{
	t_vec2u		size;
	uint32_t	maxwidth;
	size_t		i;

	size = (t_vec2u){0, FHEIGHT};
	maxwidth = 0;
	i = 0;
	while (true)
	{
		if (' ' <= str[i] && str[i] <= '~')
			size.x += font->meta[str[i] - ' '].s.x;
		else if (str[i] == '\n')
		{
			maxwidth = ft_max(2, maxwidth, size.x);
			size.y += FHEIGHT + 1;
		}
		else
			break ;
		i++;
	}
	if (!i || str[i])
		return ((t_vec2u){0, 0});
	else
		return ((t_vec2u){ft_max(2, maxwidth, size.x) * font->sc,
			size.y * font->sc});
}

bool	draw_str(mlx_image_t *img, t_font *font, const char *str, t_vec2u pos)
{
	uint32_t	i;
	t_vec2u		c;

	c = str_size(font, str);
	if (pos.x + c.x >= img->width || pos.y + c.y >= img->height)
		return (false);
	c = pos;
	i = 0;
	while (true)
	{
		if (' ' <= str[i] && str[i] <= '~')
		{
			draw_char(img, font, str[i], c);
			c.x += font->meta[str[i] - ' '].s.x * font->sc;
		}
		else if (str[i] == '\n')
			c = (t_vec2u){0, c.y + (FHEIGHT + 1) * font->sc};
		else
			break ;
		i++;
	}
	if (str[i])
		return (false);
	return (true);
}
