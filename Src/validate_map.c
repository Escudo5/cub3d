/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:13:46 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:40:33 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "../Inc/validate_map_utils.h"
#include "../libft/libft.h"

e_exit_status	normalize_map(t_map *map)
{
	char	*normalized_line;
	int		num_common_spaces;
	int		i;

	num_common_spaces = get_common_initial_space(map);
	map->width -= num_common_spaces;
	map->player_pos[0] -= num_common_spaces;
	i = -1;
	while (++i < map->height)
	{
		normalized_line = normalize_map_line(map->map[i], map->width,
				num_common_spaces);
		if (!normalized_line)
			return (ERR_FAIL_MALLOC);
		free(map->map[i]);
		map->map[i] = normalized_line;
	}
	return (SUCCESS);
}

e_exit_status	flood_fill(t_map *map, char **visited, int row, int col)
{
	if (row >= map->height || row < 0 || col < 0
		|| col >= (int)strlen(map->map[row]))
		return (printf("out of bounds\n"), ERR_MAP_IS_NOT_CLOSE);
	if (map->map[row][col] == ' ')
		return (printf("espacio encontrado\n"), ERR_MAP_IS_NOT_CLOSE);
	if (visited[row][col] == '1' || map->map[row][col] == '1')
		return (SUCCESS);
	visited[row][col] = '1';
	if (SUCCESS != flood_fill(map, visited, row - 1, col))
		return (ERR_MAP_IS_NOT_CLOSE);
	if (SUCCESS != flood_fill(map, visited, row + 1, col))
		return (ERR_MAP_IS_NOT_CLOSE);
	if (SUCCESS != flood_fill(map, visited, row, col + 1))
		return (ERR_MAP_IS_NOT_CLOSE);
	if (SUCCESS != flood_fill(map, visited, row, col - 1))
		return (ERR_MAP_IS_NOT_CLOSE);
	return (SUCCESS);
}

e_exit_status	check_map_is_closed(t_map *map)
{
	e_exit_status	status;
	char			**visited;
	int				i;
	int				line_size;

	visited = (char **)malloc((map->height + 1) * (sizeof(char *)));
	if (!visited)
		return (ERR_FAIL_MALLOC);
	i = -1;
	while (++i < map->height)
	{
		line_size = ft_strlen(map->map[i]);
		visited[i] = (char *)malloc((line_size + 1) * sizeof(char));
		if (!visited[i])
			return (ft_free_matrix(visited), ERR_FAIL_MALLOC);
		ft_memset(visited[i], '0', line_size);
		visited[i][line_size] = '\0';
	}
	visited[i] = NULL;
	status = flood_fill(map, visited, map->player_pos[1], map->player_pos[0]);
	ft_free_matrix(visited);
	return (status);
}

e_exit_status	validate_map(t_map *map)
{
	e_exit_status	status;

	status = normalize_map(map);
	if (SUCCESS != status)
		return (status);
	status = check_map_is_closed(map);
	return (status);
}
