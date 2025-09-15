/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:45:00 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 13:54:37 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"

void	draw_controls_help(t_mlx *mlx)
{
    mlx_string_put(mlx->mlx, mlx->win, 20, 40,
        MENU_COLOR_STR, "W: Move forward");
    mlx_string_put(mlx->mlx, mlx->win, 20, 60,
        MENU_COLOR_STR, "S: Move backward");
    mlx_string_put(mlx->mlx, mlx->win, 20, 80,
        MENU_COLOR_STR, "A: Move left");
    mlx_string_put(mlx->mlx, mlx->win, 20, 100,
        MENU_COLOR_STR, "D: Move right");
    mlx_string_put(mlx->mlx, mlx->win, 20, 120,
        MENU_COLOR_STR, "Left/Right: Rotate");
    mlx_string_put(mlx->mlx, mlx->win, 20, 140,
        MENU_COLOR_STR, "M: Toggle menu");
    mlx_string_put(mlx->mlx, mlx->win, 20, 160,
        MENU_COLOR_STR, "+/-: Change speed");
}

void	draw_menu_background(t_mlx *mlx)
{
    int	y;
    int	x;

    y = -1;
    while (++y < WIN_HEIGHT)
    {
        x = -1;
        while (++x < MENU_WIDTH)
            my_pixel_put(mlx, x, y, MENU_COLOR);
    }
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
