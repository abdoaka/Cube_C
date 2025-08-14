/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:00:04 by marvin            #+#    #+#             */
/*   Updated: 2025/08/14 02:00:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	parse_color_value(char *value)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(value, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_split(rgb);
		error("Invalid color format");
	}
	if (!is_all_digits(rgb[0])
		|| !is_all_digits(rgb[1])
		|| !is_all_digits(rgb[2]))
	{
		free_split(rgb);
		error("Invalid color format");
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error("Color values out of range");
	return ((r << 16) | (g << 8) | b);
}

static void	parse_texture(char *key, char *value, t_config *cfg)
{
	if (!ft_strncmp(key, "NO", 3))
		cfg->texture_no = value;
	else if (!ft_strncmp(key, "SO", 3))
		cfg->texture_so = value;
	else if (!ft_strncmp(key, "WE", 3))
		cfg->texture_we = value;
	else if (!ft_strncmp(key, "EA", 3))
		cfg->texture_ea = value;
	else
	{
		free(value);
		error("Unknown texture key");
	}
}

static void	parse_floor_ceiling(char *key, char *value, t_config *cfg)
{
	int	color;

	color = parse_color_value(value);
	if (!ft_strncmp(key, "F", 2))
		cfg->floor_color = color;
	else if (!ft_strncmp(key, "C", 2))
		cfg->ceiling_color = color;
	else
	{
		error("Unknown color key");
	}
}

void	parse_config_line(char *line, t_config *cfg)
{
	char	**parts;
	char	*value;

	parts = ft_split(str_trim(line), ' ');
	if (!parts || !parts[0] || !parts[1])
		error("Invalid config line");
	value = str_trim(parts[1]);
	if (!ft_strncmp(parts[0], "NO", 3) || !ft_strncmp(parts[0], "SO", 3)
		|| !ft_strncmp(parts[0], "WE", 3) || !ft_strncmp(parts[0], "EA", 3))
		parse_texture(parts[0], value, cfg);
	else if (!ft_strncmp(parts[0], "F", 2) || !ft_strncmp(parts[0], "C", 2))
		parse_floor_ceiling(parts[0], value, cfg);
	else
	{
		free(value);
		error("Unknown config key");
	}
	free_split(parts);
}
