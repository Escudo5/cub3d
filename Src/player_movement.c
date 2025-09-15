/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:13:33 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 14:28:48 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../Inc/cube.h"
#include "../Inc/player_utils.h"

#include <math.h>

// Rotación ahora está en player.c

// Declaración en player_utils.c
void handle_movement(t_scene *scene, t_map *map);

// Auxiliares para movimiento
// Implementación en player_utils.c


void	move_player(t_scene *scene, t_map *map)
{
	handle_rotation(scene);
	handle_movement(scene, map);
}
