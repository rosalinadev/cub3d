/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdunatte <vdunatte@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:00:46 by vdunatte          #+#    #+#             */
/*   Updated: 2025/07/19 00:10:36 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include "assets.h"
#include "error.h"

static bool	get_path_num(char *line, char **path, uint32_t *frames)
{
	size_t	len;

	if (*path != NULL)
		return (eno(E_META_DUPL), false);
	while (*line == ' ')
		line++;
	len = ft_strcspn(line, " ");
	*path = ft_calloc(len + FRAME_SIZE + 1, 1);
	if (*path == NULL)
		return (eno(E_MEM), false);
	ft_strlcat(*path, line, len + 1);
	if (frames)
	{
		line += len;
		while (*line == ' ')
			line++;
		len = ft_strspn(line, "0123456789");
		if (!len || len > 9)
			return (eno(E_FRAMES), false);
		*frames = ft_atoi(line);
		if (!*frames)
			return (eno(E_FRAMES), false);
	}
	return (true);
}

static bool	get_color(char *line, t_col *col)
{
	int		i;
	int		val;
	size_t	len;

	if (col->col)
		return (eno(E_META_DUPL), false);
	while (*line == ' ')
		line++;
	i = 0;
	while (i < 3)
	{
		len = ft_strspn(line, "0123456789");
		if (!len || len > 3)
			return (eno(E_META_COL_RANGE), false);
		val = ft_atoi(line);
		if (val % 0x100 != val)
			return (eno(E_META_COL_RANGE), false);
		col->rgba[i] = val;
		line += len;
		if (++i < 3 && *line++ != ',')
			return (eno(E_META_COL_FMT), false);
	}
	col->a = 0xFF;
	return (true);
}

static bool	match(char *line, t_meta *meta, bool is_bonus)
{
	if (ft_strlen(line) < 2)
		return (eno(E_META_IDENT), false);
	if (line[0] == 'N' && line[1] == 'O')
		return (get_path_num(&line[2], &meta->path[A_N], NULL));
	if (line[0] == 'S' && line[1] == 'O')
		return (get_path_num(&line[2], &meta->path[A_S], NULL));
	if (line[0] == 'W' && line[1] == 'E')
		return (get_path_num(&line[2], &meta->path[A_W], NULL));
	if (line[0] == 'E' && line[1] == 'A')
		return (get_path_num(&line[2], &meta->path[A_E], NULL));
	if (line[0] == 'C')
		return (get_color(&line[1], &meta->ceil));
	if (line[0] == 'F')
		return (get_color(&line[1], &meta->floor));
	if (is_bonus)
	{
		if (line[0] == 'D')
			return (get_path_num(&line[1], &meta->path[A_DOOR], NULL));
		if (line[0] == 'S' && line[1] == 'P')
			return (get_path_num(&line[2], &meta->sprite_dir,
					&meta->sprite_frames));
	}
	return (eno(E_META_IDENT), false);
}

static bool	check(t_meta *meta, bool is_bonus)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (meta->path[i] == NULL)
			return (false);
		i++;
	}
	if (!meta->ceil.col || !meta->floor.col)
		return (false);
	if (is_bonus == true)
		if (meta->path[A_DOOR] == NULL || meta->sprite_dir == NULL
			|| meta->sprite_frames == 0)
			return (false);
	return (true);
}

bool	parse_meta(int fd, t_meta *meta, bool is_bonus)
{
	char	*line;
	int		i;

	if (check(meta, is_bonus))
		return (true);
	line = get_next_line(fd);
	if (line == NULL)
		return (eno(E_META_EOF), false);
	if (ft_strchr(line, '\n'))
		*ft_strchr(line, '\n') = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] && !match(&(line[i]), meta, is_bonus))
		return (free(line), false);
	free(line);
	return (parse_meta(fd, meta, is_bonus));
}
