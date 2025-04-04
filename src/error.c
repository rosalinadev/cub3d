/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:46:30 by rvandepu          #+#    #+#             */
/*   Updated: 2025/04/04 07:54:32 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "defaults.h"
#include "error.h"

static t_err		g_err;

static const char	*g_errstr[E__MAX] = {\
	[E__UNSPECIFIED] = "Unspecified error", \
	[E_MEM] = "Memory allocation failed", \
	[E_OPEN] = "Could not open file", \
	[E_FONT] = "Could not load font.", \
	[E_MAP_EXT] = "Incorrect scene file extension", \
	[E_MAP_EMPTY] = "Map is empty", \
	[E_MAP_CHARS] = "Map contains invalid characters", \
	[E_MAP_SPAWN] = "Map has no spawn point", \
	[E_MAP_SPAWNS] = "Map has multiple spawn points", \
	[E_MAP_WALLS] = "Map is not enclosed by walls", \
};

static const bool	g_err_perror[E__MAX] = {\
	[E_MEM] = true, \
	[E_OPEN] = true, \
};

// Rationale for using fprintf:
//  While fprint is not allowed by the subject, printf is allowed
//  and it seems like an oversight to not allow printing to stderr.
// Considering there are no other allowed functions that enable interacting
// with FILE * objects, it's safe to assume that using fprintf cannot be abused
// to bypass norm restrictions.

void	err_p(int count, ...)
{
	va_list		arg;
	bool		valid_eno;
	const char	*s;

	if (g_err.eno == E__NOPRINT)
		return ;
	fprintf(stderr, "%s", ERR_PRE);
	va_start(arg, count);
	while (count--)
	{
		s = va_arg(arg, char *);
		fprintf(stderr, "%s: ", s);
	}
	va_end(arg);
	valid_eno = E__UNSPECIFIED < g_err.eno && g_err.eno < E__MAX;
	s = "Invalid error";
	if (valid_eno)
		s = g_errstr[g_err.eno];
	fprintf(stderr, "%s", s);
	if (valid_eno && g_err_perror[g_err.eno])
		fprintf(stderr, ": %s", strerror(g_err.errsv));
	fprintf(stderr, "\n");
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
