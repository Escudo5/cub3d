
#include "../Inc/cube.h"
#include "../Inc/handlers_utils.h"
#include "../libft/libft.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarquez <smarquez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:13:13 by smarquez          #+#    #+#             */
/*   Updated: 2025/09/15 14:25:50 by smarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

e_exit_status handler_empty(char *line, t_map *map, t_mealy *machine)
{
	(void)line;
	(void)map;
	(void)machine;
	return (SUCCESS);
}

e_exit_status handler_error(char *line, t_map *map, t_mealy *machine)
{
	(void)line;
	(void)map;
	(void)machine;
	return (ERR_PARSER);
}

e_exit_status handler_eof(char *line, t_map *map, t_mealy *machine)
{
	(void)line;
	if ((machine->tokens_mask & 0x7F) != 0x7F)
		return (ERR_INVALID_MAP);
	if (map->height == 0)
		return (ERR_INVALID_MAP);
	return (SUCCESS);
}

e_exit_status	valid_texture(char *line)
{
	char	*tmp;
	int		fd;

	tmp = ft_strnstr(line, ".xpm", ft_strlen(line));
	if (!tmp)
		return (ERR_BAD_EXTENSION);
	tmp += 4;
	if (*tmp != '\n' && *tmp != '\0')
		return (ERR_INVALID_TEXTURE);
	*tmp = '\0';
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (ERR_INVALIAD_ROUTE_MAP);
	close(fd);
	return (SUCCESS);
}

e_exit_status	valid_rgb(char *line)
{
	char	*tmp;
	int		color;
	int		i;

	tmp = line;
	i = -1;
	while (++i < 3)
	{
		color = ft_atoi(tmp);
		if (color < 0 || color > 255)
			return (ERR_INVALID_COLOR_RANGE);
		while (ft_isdigit(*tmp))
			tmp++;
		if (i < 2)
		{
			if (*tmp != ',')
				return (ERR_INVALID_COLOR_FORMAT);
			tmp++;
		}
	}
	while (*tmp == ' ')
		tmp++;
	if (*tmp != '\n' && *tmp != '\0')
		return (ERR_INVALID_COLOR_FORMAT);
	if (*tmp == '\n')
		*tmp = '\0';
	return (SUCCESS);
}

e_exit_status	valid_mapline(char *line, t_map *map, t_mealy *machine,
		int *width)
{
	char	*tmp;

	tmp = line;
	*width = 0;
	while (*tmp && *tmp != '\n')
	{
		if (!ft_strchr("01 NSEW", *tmp))
			return (ERR_INVALID_MAP_CHAR);
		if (ft_strchr("NSEW", *tmp) && (machine->tokens_mask & (1 << 6)))
			return (ERR_DUPLICATED_PLAYER);
		if (ft_strchr("NSEW", *tmp))
		{
			machine->tokens_mask |= (1 << 6);
			map->player_pos[0] = *width;
			map->player_pos[1] = map->height;
			map->orientation = *tmp;
			*tmp = '0';
		}
		(*width)++;
		if (*tmp == '1' && *(tmp + 1) == ' ')
			break ;
		tmp++;
	}
	return (SUCCESS);
}

int	parse_rgb_to_int(char *rgb_str)
{
	int		r;
	int		g;
	int		b;
	char	*ptr;

	ptr = rgb_str;
	r = ft_atoi(ptr);
	while (*ptr && *ptr != ',')
		ptr++;
	if (*ptr != ',')
		return (-1);
	ptr++;
	g = ft_atoi(ptr);
	while (*ptr && *ptr != ',')
		ptr++;
	if (*ptr != ',')
		return (-1);
	ptr++;
	b = ft_atoi(ptr);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
