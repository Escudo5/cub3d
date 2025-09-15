/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:07:56 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:56:37 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "player_utils.h"
#include <math.h>

void handle_rotation_right(t_scene *scene);

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
	camera->dir_x = camera->dir_x * cos(-rot_speed) - camera->dir_y
		* sin(-rot_speed);
	camera->dir_y = old_dir_x * sin(-rot_speed) + camera->dir_y
		* cos(-rot_speed);
	camera->plane_x = camera->plane_x * cos(-rot_speed) - camera->plane_y
		* sin(-rot_speed);
	camera->plane_y = old_plane_x * sin(-rot_speed) + camera->plane_y
		* cos(-rot_speed);
}

void	handle_rotation(t_scene *scene)
{
	if (scene->controls.rotate_left)
		handle_rotation_left(scene);
	if (scene->controls.rotate_right)
		handle_rotation_right(scene);
}

static void	move_forward(t_camera *camera, t_map *map, float move_speed)
{
	float	new_x;
	float	new_y;

	new_x = camera->pos_x + camera->dir_x * move_speed;
	new_y = camera->pos_y + camera->dir_y * move_speed;
	if (map->map[(int)camera->pos_y][(int)new_x] == '0')
		camera->pos_x = new_x;
	if (map->map[(int)new_y][(int)camera->pos_x] == '0')
		camera->pos_y = new_y;
}

static void	move_backward(t_camera *camera, t_map *map, float move_speed)
{
	float	new_x;
	float	new_y;

	new_x = camera->pos_x - camera->dir_x * move_speed;
	new_y = camera->pos_y - camera->dir_y * move_speed;
	if (map->map[(int)camera->pos_y][(int)new_x] == '0')
		camera->pos_x = new_x;
	if (map->map[(int)new_y][(int)camera->pos_x] == '0')
		camera->pos_y = new_y;
}

static void	strafe_left(t_camera *camera, t_map *map, float move_speed)
{
	float	left_x;
	float	left_y;
	float	new_x;
	float	new_y;

	left_x = camera->dir_y;
	left_y = -camera->dir_x;
	new_x = camera->pos_x + left_x * move_speed;
	new_y = camera->pos_y + left_y * move_speed;
	if (map->map[(int)camera->pos_y][(int)new_x] == '0')
		camera->pos_x = new_x;
	if (map->map[(int)new_y][(int)camera->pos_x] == '0')
		camera->pos_y = new_y;
}

static void	strafe_right(t_camera *camera, t_map *map, float move_speed)
{
	float	right_x;
	float	right_y;
	float	new_x;
	float	new_y;

	right_x = -camera->dir_y;
	right_y = camera->dir_x;
	new_x = camera->pos_x + right_x * move_speed;
	new_y = camera->pos_y + right_y * move_speed;
	if (map->map[(int)camera->pos_y][(int)new_x] == '0')
		camera->pos_x = new_x;
	if (map->map[(int)new_y][(int)camera->pos_x] == '0')
		camera->pos_y = new_y;
}

void	handle_movement(t_scene *scene, t_map *map)
{
	t_camera	*camera;
	float		move_speed;

	camera = &scene->camera;
	move_speed = scene->params.trasnlation_speed;
	if (move_speed > 0.9f)
		move_speed = 0.9f;
	if (scene->controls.key_up)
		move_forward(camera, map, move_speed);
	if (scene->controls.key_down)
		move_backward(camera, map, move_speed);
	if (scene->controls.key_right)
		strafe_right(camera, map, move_speed);
	if (scene->controls.key_left)
		strafe_left(camera, map, move_speed);
}

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
	camera->dir_x = camera->dir_x * cos(rot_speed) - camera->dir_y
		* sin(rot_speed);
	camera->dir_y = old_dir_x * sin(rot_speed) + camera->dir_y * cos(rot_speed);
	camera->plane_x = camera->plane_x * cos(rot_speed) - camera->plane_y
		* sin(rot_speed);
	camera->plane_y = old_plane_x * sin(rot_speed) + camera->plane_y
		* cos(rot_speed);
}
