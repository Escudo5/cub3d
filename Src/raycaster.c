/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:13:41 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:34:22 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

// Un rayo por linea vertacal de pixeles en la pantalla
void init_ray(t_dda *dda, t_camera *camera, int col)
{
	double cameraX;
	cameraX = 2.0 * col / (double)WIN_WIDTH - 1.0;
	dda->rayDir_x = camera->dir_x + camera->plane_x * cameraX;
	dda->rayDir_y = camera->dir_y + camera->plane_y * cameraX;
	dda->map_x = (int)camera->pos_x;
	dda->map_y = (int)camera->pos_y;
	if (dda->rayDir_x == 0)
		dda->deltaDist_x = 1e30;
	else
		dda->deltaDist_x = fabs(1.0 / dda->rayDir_x);
	if (dda->rayDir_y == 0)
		dda->deltaDist_y = 1e30;
	else
		dda->deltaDist_y = fabs(1.0 / dda->rayDir_y);
	dda->hit = 0;
	dda->side = 0;
}

void draw_wall_stripe(t_mlx *mlx, t_dda *dda, int col, t_map *map, t_camera *camera)
{
	int color;
	char *tex_addr = NULL;
	int tex_width = 0, tex_height = 0;
	int tex_bpp = 0, tex_lpl = 0;
	// Selecciona la textura y sus datos
	if (dda->side == 0 && dda->rayDir_x > 0) {
		tex_addr = map->addr_ea;
		tex_bpp = map->bpp_ea;
		tex_lpl = map->lpl_ea;
		tex_width = map->width_ea;
		tex_height = map->height_ea;
	} else if (dda->side == 0 && dda->rayDir_x < 0) {
		tex_addr = map->addr_we;
		tex_bpp = map->bpp_we;
		tex_lpl = map->lpl_we;
		tex_width = map->width_we;
		tex_height = map->height_we;
	} else if (dda->side == 1 && dda->rayDir_y > 0) {
		tex_addr = map->addr_so;
		tex_bpp = map->bpp_so;
		tex_lpl = map->lpl_so;
		tex_width = map->width_so;
		tex_height = map->height_so;
	} else if (dda->side == 1 && dda->rayDir_y < 0) {
		tex_addr = map->addr_no;
		tex_bpp = map->bpp_no;
		tex_lpl = map->lpl_no;
		tex_width = map->width_no;
		tex_height = map->height_no;
	}

	double perpWallDist = dda->wallDist;
	if (perpWallDist <= 0.0001)
		perpWallDist = 0.0001;
	int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
	int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	int y = 0;
	while (y < drawStart)
		my_pixel_put(mlx, col, y++, map->color_floor);
	// Renderizar pared con textura
	double wallX;
	int tex_x, tex_y;
	if (dda->side == 0)
		wallX = camera->pos_y + perpWallDist * dda->rayDir_y;
	else
		wallX = camera->pos_x + perpWallDist * dda->rayDir_x;
	wallX -= floor(wallX);
	tex_x = (int)(wallX * (double)tex_width);
	if ((dda->side == 0 && dda->rayDir_x > 0) || (dda->side == 1 && dda->rayDir_y < 0))
		tex_x = tex_width - tex_x - 1;
	for (; y <= drawEnd; y++) {
		int d = y * 256 - WIN_HEIGHT * 128 + lineHeight * 128;
		tex_y = ((d * tex_height) / lineHeight) / 256;
		// Comprobaciones de seguridad
		if (!tex_addr) {
			color = 0xFF00FF; // fallback magenta si no hay textura
		} else if (tex_x < 0 || tex_x >= tex_width || tex_y < 0 || tex_y >= tex_height) {
			color = 0x00FFFF; // fallback cyan si coordenadas fuera de rango
		} else {
			color = *(unsigned int *)(tex_addr + (tex_y * tex_lpl + tex_x * tex_bpp / 8));
		}
		my_pixel_put(mlx, col, y, color);
	}
	while (y <= WIN_HEIGHT)
		my_pixel_put(mlx, col, y++, map->color_ceiling);
}

// Me muevo de mi posicion en la celda a cortar el grid
void	calculate_step_and_sidedist(t_dda *dda, t_camera *camera)
{
	if (dda->rayDir_x < 0)
	{
		dda->step_x = -1;
		dda->sideDist_x = (camera->pos_x - (double)dda->map_x)
			* dda->deltaDist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->sideDist_x = ((double)dda->map_x + 1.0 - camera->pos_x)
			* dda->deltaDist_x;
	}
	if (dda->rayDir_y < 0)
	{
		dda->step_y = -1;
		dda->sideDist_y = (camera->pos_y - (double)dda->map_y)
			* dda->deltaDist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->sideDist_y = ((double)dda->map_y + 1.0 - camera->pos_y)
			* dda->deltaDist_y;
	}
}

// Avanzo a la consecutivas lineas del grid,
	//siempre una unidad ya sea abscisa u ordenada
// Determino si la pared es vertical u horizontal
void	perform_dda(t_dda *dda, t_map *map)
{
	while (!dda->hit)
	{
		if (dda->sideDist_x < dda->sideDist_y)
		{
			dda->sideDist_x += dda->deltaDist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->sideDist_y += dda->deltaDist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_x < 0 || dda->map_x >= map->width || dda->map_y < 0
			|| dda->map_y >= map->height)
		{
			dda->hit = 1;
			break ;
		}
		if (map->map[dda->map_y][dda->map_x] != '0')
		{
			dda->hit = 1;
		}
	}
}

void	calculate_wall_distance(t_dda *dda)
{
	if (dda->side == 0)
	{
		dda->wallDist = (dda->sideDist_x - dda->deltaDist_x);
	}
	else
	{
		dda->wallDist = (dda->sideDist_y - dda->deltaDist_y);
	}
}

// void	draw_wall_stripe(t_mlx *mlx, t_dda *dda, int col, t_map *map)
// {
//     // Old implementation removed
// }
