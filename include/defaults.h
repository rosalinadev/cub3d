/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 05:39:29 by rvandepu          #+#    #+#             */
/*   Updated: 2025/07/09 14:52:29 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTS_H
# define DEFAULTS_H

# define NAME "cub3D"
# define MAP_EXT ".cub"
# define BONUS_SUFFIX "_bonus"

# define ERR_PRE "Error\n"

# define FONT_PATH "assets/hall-fetica-bold.png"
# define FONT_SCALE 1

# define START_FULLSCREEN false
# define START_PAUSED false
# define WIDTH 1280
# define HEIGHT 720

# define FPS 90
# define RENDER_DISTANCE 256
# define FOV 90 // deg

# define MOV_SPEED 5.0 // cells/s
// in radians/second
# define ROT_SPEED 3.0 // rad/s
# define ROT_PER_PX 0.002 // rad/px
# define SPRINT_BOOST 1.0 // +100%

#endif
