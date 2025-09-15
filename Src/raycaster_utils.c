/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:13:27 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:13:28 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"

void draw_wall_stripe_utils(t_mlx *mlx, t_dda *dda, int col, t_map *map)
{
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		y;
	int color;
	perpWallDist = dda->wallDist;
	if (perpWallDist <= 0.0001)
		perpWallDist = 0.0001;
	lineHeight = (int)(WIN_HEIGHT / perpWallDist);
	drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	if (dda->side == 1)
		color = 0x808080;
	else
		color = 0xFFFFFF;
	y = 0;
	while (y < drawStart)
		my_pixel_put(mlx, col, y++, map->color_floor);
	while (y <= drawEnd)
		my_pixel_put(mlx, col, y++, color);
	while (y <= WIN_HEIGHT)
		my_pixel_put(mlx, col, y++, map->color_ceiling);
}
