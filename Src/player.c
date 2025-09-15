/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:13:36 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:44:10 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "player_utils.h"
#include <math.h>

void	handle_rotation(t_scene *scene)
{
	if (scene->controls.rotate_right)
		handle_rotation_right(scene);
	if (scene->controls.rotate_left)
		handle_rotation_left(scene);
}
// Funciones auxiliares para rotación
void	handle_rotation_right(t_scene *scene)
{
	t_camera	*camera;
	float		rot_speed;
	float		old_dir_x;
	float		old_plane_x;

	camera = &scene->camera;
	rot_speed = scene->params.rotation_speed;
	old_dir_x = camera->dir_x;
	old_plane_x = camera->plane_x;
	camera->dir_x = camera->dir_x * cos(-rot_speed) - camera->dir_y
		* sin(-rot_speed);
	camera->dir_y = old_dir_x * sin(-rot_speed) + camera->dir_y
		* cos(-rot_speed);
	camera->plane_x = camera->plane_x * cos(-rot_speed) - camera->plane_y
		* sin(-rot_speed);
	camera->plane_y = old_plane_x * sin(-rot_speed) + camera->plane_y
		* cos(-rot_speed);
}

void	handle_rotation_left(t_scene *scene)
{
	t_camera	*camera;
	float		rot_speed;
	float		old_dir_x;
	float		old_plane_x;

	camera = &scene->camera;
	rot_speed = scene->params.rotation_speed;
	old_dir_x = camera->dir_x;
	old_plane_x = camera->plane_x;
	camera->dir_x = camera->dir_x * cos(rot_speed) - camera->dir_y
		* sin(rot_speed);
	camera->dir_y = old_dir_x * sin(rot_speed) + camera->dir_y * cos(rot_speed);
	camera->plane_x = camera->plane_x * cos(rot_speed) - camera->plane_y
		* sin(rot_speed);
	camera->plane_y = old_plane_x * sin(rot_speed) + camera->plane_y
		* cos(rot_speed);
}

// ...existing code...

void	move_player(t_scene *scene, t_map *map)
{
	handle_rotation(scene);
	handle_movement(scene, map);
}
