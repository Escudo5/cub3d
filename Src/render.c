/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:50:54 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:34:22 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "../Inc/render_utils.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include <sys/time.h>

char	*get_fps(struct timeval frame_start)
{
	static char		buf[16];
	struct timeval	frame_end;

	double elapsed, fps;
	gettimeofday(&frame_end, NULL);
	elapsed = (frame_end.tv_sec - frame_start.tv_sec) + (frame_end.tv_usec
			- frame_start.tv_usec) / 1e6;
	if (elapsed > 0.0)
		fps = 1.0 / elapsed;
	else
		fps = 0.0;
	intToStr((int)fps, buf);
	return (buf);
}

void	perform_raycasting(t_map *map, t_mlx *mlx, t_scene *scene)
{
	int		col;
	t_dda	dda;

	col = -1;
	while (++col < WIN_WIDTH)
	{
		init_ray(&dda, &scene->camera, col);
		calculate_step_and_sidedist(&dda, &scene->camera);
		perform_dda(&dda, map);
		calculate_wall_distance(&dda);
	draw_wall_stripe(mlx, &dda, col, map, &scene->camera);
	}
}


void set_menu(t_mlx *mlx, t_controls *controls, t_params *params,
		t_camera *camera)
{
	(void)controls;
	(void)params;
	(void)camera;
	draw_menu_background(mlx);
	draw_controls_help(mlx);
}

// pensar como hago el menu, con sin minimap, ocupando todo,
// sobre el mapa renderizado o yo que coño se ajajjaja
e_exit_status	render(t_map *map, t_mlx *mlx, t_scene *scene)
{
	struct timeval	frame_start;

	gettimeofday(&frame_start, NULL);
	clear_image(mlx);
	if (scene->controls.menu)
	{
		set_menu(mlx, &scene->controls, &scene->params, &scene->camera);
		// draw_minimap(map, mlx, scene);
	}
	else
	{
		move_player(scene, map);
		perform_raycasting(map, mlx, scene);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
	// repensar donde poner el marcador de los fps
	mlx_string_put(mlx->mlx, mlx->win, WIN_HEIGHT - 100, WIN_WIDTH - 100, RED,
		get_fps(frame_start));
	return (SUCCESS);
}
