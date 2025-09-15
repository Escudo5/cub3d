/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:13:38 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:56:37 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "../Inc/print_utils.h"

void	print_map(t_map map)
{
	int	i;

	printf("\n");
	printf("PRINT MAP:\n");
	printf("Texturas:\n");
	printf("  NO: %s\n", map.texture_no);
	printf("  SO: %s\n", map.texture_so);
	printf("  WE: %s\n", map.texture_we);
	printf("  EA: %s\n", map.texture_ea);
	printf("Colores:\n");
	printf("  Suelo : %d\n", map.color_floor);
	printf("  Techo : %d\n", map.color_ceiling);
	printf("Jugador:\n");
	printf("  Posición: (%d, %d)\n", map.player_pos[0], map.player_pos[1]);
	printf("  Orientación: %c\n", map.orientation);
	printf("Dimensiones:\n Altura[%d] Anchura[%d]\n", map.height, map.width);
	printf("\n");
	printf("Mapa:\n");
	i = 0;
	while (i < map.height)
	{
		printf("%s\n", map.map[i]);
		i++;
	}
}

void	print_mlx(t_mlx mlx)
{
	printf("=== MLX DEBUG ===\n");
	printf("mlx: %p\n", mlx.mlx);
	printf("win: %p\n", mlx.win);
	printf("img: %p\n", mlx.img);
	printf("addr: %p\n", mlx.addr);
	printf("bpp: %d\n", mlx.bpp);
	printf("lpl: %d\n", mlx.lpl);
	printf("endian: %d\n", mlx.endian);
	printf("=================\n");
}

void	print_scene(t_scene scene)
{
	printf("=== Scene ===\n");
	printf("Controls:\n");
	print_scene_controls(scene);
	print_scene_params(scene);
	print_scene_camera(scene);
}

void	print_dda(t_dda dda)
{
	printf("=== DDA State ===\n");
	printf("Map position:     map_x = %d, map_y = %d\n", dda.map_x, dda.map_y);
	printf("Ray direction:    rayDir_x = %.6f, rayDir_y = %.6f\n", dda.rayDir_x,
		dda.rayDir_y);
	printf("Side distances:   sideDist_x = %.6f, sideDist_y = %.6f\n",
		dda.sideDist_x, dda.sideDist_y);
	printf("Delta distances:  deltaDist_x = %.6f, deltaDist_y = %.6f\n",
		dda.deltaDist_x, dda.deltaDist_y);
	printf("Wall distance:    wallDist = %.6f\n", dda.wallDist);
	printf("Step:             step_x = %d, step_y = %d\n", dda.step_x,
		dda.step_y);
	if (dda.hit)
		printf("Hit:              true\n");
	else
		printf("Hit:              false\n");
	printf("Side:             %d\n", dda.side);
}
