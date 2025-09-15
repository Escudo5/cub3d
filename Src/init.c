/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:13:21 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:34:22 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

void	init_controls(t_controls *controls)
{
	controls->key_up = 0;
	controls->key_down = 0;
	controls->key_right = 0;
	controls->key_left = 0;
	controls->rotate_right = 0;
	controls->rotate_left = 0;
	controls->menu = 0;
}

void	init_params(t_params *params)
{
	params->rotation_speed = 0.1;
	params->trasnlation_speed = 0.5f;
	params->block_size = 20;
	params->fieldOfView = PI / 3; // 60º
}

void	init_camera(t_camera *camera, t_map *map, t_params params)
{
	float	plane_length;

	camera->pos_x = (float)map->player_pos[0] + 0.5f;
	camera->pos_y = (float)map->player_pos[1] + 0.5f;
	if (map->orientation == 'N')
	{
		camera->dir_x = 0.0f;
		camera->dir_y = -1.0f;
	}
	else if (map->orientation == 'E')
	{
		camera->dir_x = 1.0f;
		camera->dir_y = 0.0f;
	}
	else if (map->orientation == 'S')
	{
		camera->dir_x = 0.0f;
		camera->dir_y = 1.0f;
	}
	else if (map->orientation == 'W')
	{
		camera->dir_x = -1.0f;
		camera->dir_y = 0.0f;
	}
	plane_length = tan(params.fieldOfView / 2.0f);
	camera->plane_x = -camera->dir_y * plane_length;
	camera->plane_y = camera->dir_x * plane_length;
}

void	init_scene(t_scene *scene, t_map *map)
{
	init_controls(&(scene->controls));
	init_params(&(scene->params));
	init_camera(&(scene->camera), map, scene->params);

	// Inicializar texturas solo una vez
	extern t_mlx *g_mlx;
	map->img_no = mlx_xpm_file_to_image(g_mlx->mlx, map->texture_no, &map->width_no, &map->height_no);
	map->addr_no = mlx_get_data_addr(map->img_no, &map->bpp_no, &map->lpl_no, &map->endian_no);
	map->img_so = mlx_xpm_file_to_image(g_mlx->mlx, map->texture_so, &map->width_so, &map->height_so);
	map->addr_so = mlx_get_data_addr(map->img_so, &map->bpp_so, &map->lpl_so, &map->endian_so);
	map->img_we = mlx_xpm_file_to_image(g_mlx->mlx, map->texture_we, &map->width_we, &map->height_we);
	map->addr_we = mlx_get_data_addr(map->img_we, &map->bpp_we, &map->lpl_we, &map->endian_we);
	map->img_ea = mlx_xpm_file_to_image(g_mlx->mlx, map->texture_ea, &map->width_ea, &map->height_ea);
	map->addr_ea = mlx_get_data_addr(map->img_ea, &map->bpp_ea, &map->lpl_ea, &map->endian_ea);
}
