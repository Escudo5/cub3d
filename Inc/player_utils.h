/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:35:43 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:38:58 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_UTILS_H
# define PLAYER_UTILS_H

# include "cube.h"

void	handle_rotation(t_scene *scene);
void	handle_movement(t_scene *scene, t_map *map);
void	handle_rotation_left(t_scene *scene);
void	handle_rotation_right(t_scene *scene);

void handle_rotation_right(t_scene *scene);
void handle_rotation_left(t_scene *scene);
void handle_movement(t_scene *scene, t_map *map);

#endif
