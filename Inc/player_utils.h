#ifndef PLAYER_UTILS_H
#define PLAYER_UTILS_H

#include "cube.h"

void handle_rotation(t_scene *scene);
void handle_movement(t_scene *scene, t_map *map);
void handle_rotation_left(t_scene *scene);
void handle_rotation_right(t_scene *scene);

#endif
