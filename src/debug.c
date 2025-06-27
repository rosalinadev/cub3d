/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 06:08:23 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/25 22:02:48 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdarg.h>
#include "ft_bitwise.h"
#include "libft.h"

#include "cub3d.h"
#include "defaults.h"
#include "mlx_utils.h"

#define IS 11

// returns true on error
static bool	itoa_cat(int i, char *str, size_t l)
{
	char	b[IS + 1];

	ft_itoa_buf(i, b);
	return (ft_strlcat(str, b, l) >= l);
}

// returns true on error
static bool	dtoa_cat(double d, char *str, size_t l)
{
	char	b[IS + 1];
	double	i;
	bool	e;

	e = false;
	if (d < 0)
		e |= ft_strlcat(str, "-", l) >= l;
	d = modf(fabs(d), &i);
	ft_itoa_buf(i, b);
	e |= ft_strlcat(str, b, l) >= l;
	e |= ft_strlcat(str, ".", l) >= l;
	e |= (ft_itoa_buf(d *= 10, b), d = modf(d, &i), ft_strlcat(str, b, l)) >= l;
	e |= (ft_itoa_buf(d *= 10, b), d = modf(d, &i), ft_strlcat(str, b, l)) >= l;
	e |= (ft_itoa_buf(d *= 10, b), d = modf(d, &i), ft_strlcat(str, b, l)) >= l;
	e |= (ft_itoa_buf(d *= 10, b), d = modf(d, &i), ft_strlcat(str, b, l)) >= l;
	return (e);
}

#define I "I"
#define D "D"

static void	debug_cat(char *b, size_t len, bool *enabled, ...)
{
	bool	error;
	va_list	args;
	char	*str;

	error = false;
	va_start(args, enabled);
	while (true)
	{
		str = va_arg(args, char *);
		if (!str)
			break ;
		if (ft_strcmp(str, I) == 0)
			error |= itoa_cat(va_arg(args, int), b, len);
		else if (ft_strcmp(str, D) == 0)
			error |= dtoa_cat(va_arg(args, double), b, len);
		else
			error |= ft_strlcat(b, str, len) >= len;
	}
	va_end(args);
	if (!error)
		return ;
	ft_printf((("[DEBUG] Error: debug overlay str too small!\n"
				"        Disabling ovelay.\n")));
	*enabled = false;
}

#define DEBUG_STR_SIZE 1024

void	draw_debug(t_ctx *ctx, double frametime)
{
	char		str[DEBUG_STR_SIZE];
	static bool	enabled;

	mlx_clear_image(ctx->debug);
	if (ft_bit_check(ctx->kb, P_DEBUG))
	{
		enabled = !enabled;
		ft_printf("[DEBUG] debug overlay state: %d\n", enabled);
		ctx->kb = ft_bit_clear(ctx->kb, P_DEBUG);
	}
	if (!enabled)
		return ;
	ft_bzero(str, sizeof(str));
	debug_cat(str, sizeof(str), &enabled,
		"fps (cap ", I, FPS, "): ", D, 1 / frametime, "\n",
		"pos x: ", D, ctx->player.pos.x, " y: ", D, ctx->player.pos.y, "\n",
		"dir x: ", D, ctx->player.dir.x, " y: ", D, ctx->player.dir.y, "\n",
		//"visible sprites: ", I, ft_lstsize((t_list *)ctx->ray.sprites), "\n",
		NULL);
	if (str_size(&ctx->assets.font, str).x)
		draw_str(ctx->debug, &ctx->assets.font, str, (t_vec2u){0, 0});
}
