/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:40:00 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 16:37:33 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/cube.h"
#include "../libft/libft.h"

int	get_common_initial_space(t_map *map)
{
	int	num_common_spaces;
	int	i;
	int	j;

	num_common_spaces = INT_MAX;
	i = -1;
	while (++i < map->height)
	{
		j = 0;
		while (map->map[i][j] == ' ' && j < num_common_spaces)
			j++;
		if (j < num_common_spaces)
			num_common_spaces = j;
	}
	return (num_common_spaces);
}

char	*normalize_map_line(char *src, int width, int num_common_spaces)
{
	char	*normalized_line;
	int		j;
	int		src_len;

	j = 0;
	src_len = strlen(src);
	normalized_line = (char *)malloc(sizeof(char) * (width + 1));
	if (!normalized_line)
		return (NULL);
	// Copia caracteres válidos de la fuente
	while (j < width && (j + num_common_spaces) < src_len && src[j
		+ num_common_spaces] != '\0')
	{
		normalized_line[j] = src[j + num_common_spaces];
		j++;
	}
	// Rellena el resto con espacios
	while (j < width)
	{
		normalized_line[j] = ' ';
		j++;
	}
	normalized_line[width] = '\0';
	return (normalized_line);
}
