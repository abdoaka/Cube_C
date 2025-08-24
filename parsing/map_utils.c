/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 08:38:05 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/23 11:39:53 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_cell(t_map_check data)
{
	if (data.y == 0 || data.x == 0
		|| data.y == data.h - 1 || data.x == data.w - 1)
		error("Map not closed");
	if (data.map[data.y - 1][data.x] == ' '
		|| data.map[data.y + 1][data.x] == ' '
		|| data.map[data.y][data.x - 1] == ' '
		|| data.map[data.y][data.x + 1] == ' ')
		error("Map not closed properly");
}

int	get_max_width(char **lines, int height)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (i < height)
	{
		len = ft_strlen(lines[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	*pad_line(char *line, int width)
{
	int		len;
	int		i;
	char	*new_line;

	len = ft_strlen(line);
	new_line = malloc(width + 1);
	if (!new_line)
		error("Memory allocation failed");
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
		new_line[i++] = ' ';
	new_line[i] = '\0';
	return (new_line);
}

int	is_valid_map_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
