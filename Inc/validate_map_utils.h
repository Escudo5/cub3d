#ifndef VALIDATE_MAP_UTILS_H
#define VALIDATE_MAP_UTILS_H

#include "cube.h"

int get_common_initial_space(t_map *map);
char *normalize_map_line(char *src, int width, int num_common_spaces);

#endif
