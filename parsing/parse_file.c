/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:10:24 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/14 03:00:00 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	process_line(char *line, t_config *cfg, int *map_started)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!*map_started && is_only_spaces(trimmed))
		return ;
	if (!*map_started
		&& (ft_strncmp(trimmed, "NO", 2) == 0
			|| ft_strncmp(trimmed, "SO", 2) == 0
			|| ft_strncmp(trimmed, "WE", 2) == 0
			|| ft_strncmp(trimmed, "EA", 2) == 0
			|| ft_strncmp(trimmed, "F", 1) == 0
			|| ft_strncmp(trimmed, "C", 1) == 0))
	{
		parse_config_line(trimmed, cfg);
		return ;
	}
	*map_started = 1;
	if (is_only_spaces(trimmed))
		error("Empty line inside map");
	save_map_line(cfg, line);
}

static void	validate_and_setup(t_config *cfg)
{
	int		i;
	int		width;
	char	**padded;

	if (!cfg->texture_no || !cfg->texture_so
		|| !cfg->texture_we || !cfg->texture_ea)
		error("Missing texture paths");
	if (cfg->floor_color == -1 || cfg->ceiling_color == -1)
		error("Missing floor or ceiling color");
	validate_map_characters(cfg);
	padded = pad_map(cfg->map_lines, cfg->map_height, &width);
	check_closed_map(padded, cfg->map_height, width);
	find_player(cfg);
	i = 0;
	while (i < cfg->map_height)
		free(padded[i++]);
	free(padded);
}

void	 parse_file(const char *file, t_config *cfg)
{
	int		fd;
	char	*line;
	int		map_started;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Failed to open file");
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, cfg, &map_started);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	validate_and_setup(cfg);
}
