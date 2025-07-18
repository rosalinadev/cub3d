/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:46:30 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/18 05:14:20 by vdunatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

#include "defaults.h"
#include "error.h"

static t_err		g_err;

static const char	*g_errstr[E__MAX] = {
[E__UNSPECIFIED] = "Unspecified error",
[E_MEM] = "Memory allocation failed",
[E_OPEN] = "Could not open file",
[E_MAP_EXT] = "Incorrect scene file extension",
[E_MAP_EMPTY] = "Map is empty",
[E_MAP_CHARS] = "Map contains invalid characters",
[E_MAP_SPAWN] = "Map has no spawn point",
[E_MAP_SPAWNS] = "Map has multiple spawn points",
[E_MAP_WALLS] = "Map is not enclosed by walls",
[E_META_IDENT] = "Metadata has invalid identifier (missing identifier?)",
[E_META_DUPL] = "Metadata has duplicate identifier",
[E_META_COL_RANGE] = "Metadata color outside of range 0-255",
[E_META_COL_FMT] = "Metadata color improperly formatted",
[E_META_EOF] = "End of file reached while parsing metadata",
[E_FONT] = "Font loading failed",
[E_MLX] = "Window initalization failed",
[E_SIZE] = "Window too small",
[E_TEXPATH] = "Texture missing path",
[E_TEX] = "Texture loading failed",
[E_FRAMES] = "Invalid number of sprite frames",
[E_IMG] = "Failed to create MLX42 image",
[E_DISP] = "Failed to display image on window",
};

static const bool	g_err_perror[E__MAX] = {
[E_MEM] = true,
[E_OPEN] = true,
};

// Thank you 42 for not making fprintf an allowed function <3
void	err_p(int count, ...)
{
	va_list		arg;
	bool		valid_eno;
	const char	*s;

	if (g_err.eno == E__NOPRINT)
		return ;
	ft_fprintf(stderr, "%s", ERR_PRE);
	va_start(arg, count);
	while (count--)
	{
		s = va_arg(arg, char *);
		ft_fprintf(stderr, "%s: ", s);
	}
	va_end(arg);
	valid_eno = E__UNSPECIFIED < g_err.eno && g_err.eno < E__MAX;
	s = "Invalid error";
	if (valid_eno)
		s = g_errstr[g_err.eno];
	ft_fprintf(stderr, "%s", s);
	if (valid_eno && g_err_perror[g_err.eno])
		ft_fprintf(stderr, ": %s", strerror(g_err.errsv));
	ft_fprintf(stderr, "\n");
	g_err.eno = E__UNSPECIFIED;
}

void	eno(t_eno enosv)
{
	g_err.eno = enosv;
	g_err.errsv = errno;
}

void	enosv(t_eno enosv, int errsv)
{
	eno(enosv);
	g_err.errsv = errsv;
}
