/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 04:46:54 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/18 05:06:51 by vdunatte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_eno
{
	E__NOPRINT = -1,
	E__UNSPECIFIED = 0,
	E_MEM,
	E_OPEN,
	E_MAP_EXT,
	E_MAP_EMPTY,
	E_MAP_CHARS,
	E_MAP_SPAWN,
	E_MAP_SPAWNS,
	E_MAP_WALLS,
	E_META_IDENT,
	E_META_DUPL,
	E_META_COL_RANGE,
	E_META_COL_FMT,
	E_META_EOF,
	E_FONT,
	E_MLX,
	E_SIZE,
	E_TEXPATH,
	E_TEX,
	E_FRAMES,
	E_IMG,
	E_DISP,
	E__MAX
}	t_eno;

typedef struct s_err
{
	t_eno	eno;
	int		errsv;
}	t_err;

void	err_p(int count, ...);
void	eno(t_eno enosv);
void	enosv(t_eno enosv, int errsv);

#endif
