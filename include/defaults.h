/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 05:39:29 by rvandepu          #+#    #+#             */
/*   Updated: 2025/06/21 17:14:05 by rvandepu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFAULTS_H
# define DEFAULTS_H

# define NAME "cub3D"
# define MAP_EXT ".cub"

# define ERR_PRE "Error\n"

# define START_FULLSCREEN false
# if 0
#  define WIDTH 640
#  define HEIGHT 480
# else
#  define WIDTH 1920
#  define HEIGHT 1080
# endif
# define FPS 90
# define RENDER_DISTANCE 256
# define FOV 90 // deg
# define MOV_SPEED 5.0 // cells/s
// in radians/second
# define ROT_SPEED 3.0 // rad/s
# define SPRINT_BOOST 1.0 // +100%

# define DISABLE_BONUS false

#endif
