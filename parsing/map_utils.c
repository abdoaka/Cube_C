/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 08:38:05 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/13 09:22:42 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_cell(char **map, int y, int x, int h, int w)
{
	if (y == 0 || x == 0 || y == h - 1 || x == w - 1)
		error("Map not closed");
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
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

/* Fill a single line with padding */
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
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' ||
		c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

/* Return 1 if c is a player character, 0 otherwise */
int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}