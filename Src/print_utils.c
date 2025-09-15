/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:30:00 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:36:16 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"

void	print_scene_controls(t_scene scene)
{
	printf("  key_up: ");
	if (scene.controls.key_up)
		printf("true\n");
	else
		printf("false\n");
	printf("  key_down: ");
	if (scene.controls.key_down)
		printf("true\n");
	else
		printf("false\n");
	printf("  key_right: ");
	if (scene.controls.key_right)
		printf("true\n");
	else
		printf("false\n");
	printf("  key_left: ");
	if (scene.controls.key_left)
		printf("true\n");
	else
		printf("false\n");
	printf("  rotate_right: ");
	if (scene.controls.rotate_right)
		printf("true\n");
	else
		printf("false\n");
	printf("  rotate_left: ");
	if (scene.controls.rotate_left)
		printf("true\n");
	else
		printf("false\n");
}

void	print_scene_params(t_scene scene)
{
	printf("Parameters:\n");
	printf("  rotation_speed: %.6f\n", scene.params.rotation_speed);
	printf("  translation_speed: %f\n", scene.params.trasnlation_speed);
	printf("  block_size: %d\n", scene.params.block_size);
	printf("  fieldOfView: %.6f\n", scene.params.fieldOfView);
}

void	print_scene_camera(t_scene scene)
{
	printf("Camera:\n");
	printf("  pos_x: %.6f\n", scene.camera.pos_x);
	printf("  pos_y: %.6f\n", scene.camera.pos_y);
	printf("  dir_x: %.6f\n", scene.camera.dir_x);
	printf("  dir_y: %.6f\n", scene.camera.dir_y);
	printf("  plane_x: %.6f\n", scene.camera.plane_x);
	printf("  plane_y: %.6f\n", scene.camera.plane_y);
}
