/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:22:11 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/14 01:21:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	save_map_line(t_config *cfg, char *line)
{
	int		i;
	char	**new_lines;

	i = 0;
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	new_lines = malloc(sizeof(char *) * (cfg->map_height + 2));
	if (!new_lines)
		error("Memory allocation failed");
	while (i < cfg->map_height)
	{
		new_lines[i] = cfg->map_lines[i];
		i++;
	}
	new_lines[cfg->map_height] = ft_strdup(line);
	new_lines[cfg->map_height + 1] = NULL;
	free(cfg->map_lines);
	cfg->map_lines = new_lines;
	cfg->map_height++;
}

char	**pad_map(char **lines, int height, int *width_out)
{
	char	**padded;
	int		i;
	int		max_width;

	max_width = get_max_width(lines, height);
	*width_out = max_width;
	padded = malloc(sizeof(char *) * (height + 1));
	if (!padded)
		error("Memory allocation failed");
	i = 0;
	while (i < height)
	{
		padded[i] = pad_line(lines[i], max_width);
		i++;
	}
	padded[height] = NULL;
	return (padded);
}

void	validate_map_characters(t_config *cfg)
{
	int		y;
	int		x;
	int		player_count;
	char	c;

	y = 0;
	player_count = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (cfg->map_lines[y][x])
		{
			c = cfg->map_lines[y][x];
			if (!is_valid_map_char(c))
				error("Invalid character in map");
			if (is_player_char(c))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		error("Map must have exactly one player");
}

void	check_closed_map(char **map, int h, int w)
{
	int			y;
	int			x;
	char		c;
	t_map_check	data;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			c = map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				data.map = map;
				data.y = y;
				data.x = x;
				data.h = h;
				data.w = w;
				check_cell(data);
			}
			x++;
		}
		y++;
	}
}
