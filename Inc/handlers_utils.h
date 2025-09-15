#ifndef HANDLERS_UTILS_H
#define HANDLERS_UTILS_H

#include "structs.h"

e_exit_status handler_empty(char *line, t_map *map, t_mealy *machine);
e_exit_status handler_error(char *line, t_map *map, t_mealy *machine);
e_exit_status handler_eof(char *line, t_map *map, t_mealy *machine);
e_exit_status valid_texture(char *line);
e_exit_status valid_rgb(char *line);
e_exit_status valid_mapline(char *line, t_map *map, t_mealy *machine, int *width);
int parse_rgb_to_int(char *rgb_str);

#endif
