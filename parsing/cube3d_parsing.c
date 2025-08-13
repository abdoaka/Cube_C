/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkharbac <zkharbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:07:37 by zkharbac          #+#    #+#             */
/*   Updated: 2025/08/13 08:52:47 by zkharbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


// ---------- PARSING HELPERS ----------

// Parse and store texture paths and floor/ceiling colors
void parse_config_line(char *line, t_config *cfg)
{
    // Trim line before split to avoid trailing spaces
    char *trimmed_line = str_trim(line);
	char **parts = ft_split(trimmed_line, ' ');
	free(trimmed_line);

    if (!parts || !parts[0] || !parts[1])
        error("Invalid config line");

    // Trim path or color string too
    char *value = str_trim(parts[1]);

    if (!ft_strncmp(parts[0], "NO", 3))
        cfg->texture_no = value;
    else if (!ft_strncmp(parts[0], "SO", 3))
        cfg->texture_so = value;
    else if (!ft_strncmp(parts[0], "WE", 3))
        cfg->texture_we = value;
    else if (!ft_strncmp(parts[0], "EA", 3))
        cfg->texture_ea = value;
    else if (!ft_strncmp(parts[0], "F", 2) || !ft_strncmp(parts[0], "C", 2))
    {
        // Parse color: split by commas
        char **rgb = ft_split(value, ',');
        free(value);
        int count = 0;
        while (rgb[count])
            count++;
        if (count != 3)
        {
            free_split(rgb);
            error("Invalid color format");
        }
        // Validate all parts are digits and in 0-255 range
        int i = 0;
        while (i < 3)
        {
            char *part_trim = str_trim(rgb[i]);
            if (!is_all_digits(part_trim))
            {
                free(part_trim);
                free_split(rgb);
                error("Invalid color format");
            }
            int val = ft_atoi(part_trim);
            free(part_trim);
            if (val < 0 || val > 255)
            {
                free_split(rgb);
                error("Color values out of range");
            }
            i++;
        }
        int r = ft_atoi(rgb[0]);
        int g = ft_atoi(rgb[1]);
        int b = ft_atoi(rgb[2]);
        free_split(rgb);
        int color = (r << 16) | (g << 8) | b;
        if (parts[0][0] == 'F')
            cfg->floor_color = color;
        else
            cfg->ceiling_color = color;
    }
    else
    {
        free(value);
        error("Unknown config key");
    }
    free_split(parts);
}

// Find player position and direction, replace player char in map with '0'
void	find_player(t_config *cfg)
{
	int y;
	int x;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (cfg->map_lines[y][x])
		{
			char c = cfg->map_lines[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				cfg->player_x = x + 0.5f;
				cfg->player_y = y + 0.5f;
				cfg->player_dir = c;
				cfg->map_lines[y][x] = '0';
				return;
			}
			x++;
		}
		y++;
	}
	error("Player not found");
}

// ---------- MAIN PARSING FUNCTION ----------

void parse_file(const char *file, t_config *cfg)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Failed to open file");

	int map_started = 0;
	char *line;
	int i; 

	while ((line = get_next_line(fd)))
	{
		char *trimmed = skip_spaces(line);

		// Check if line is empty or contains only spaces
		int only_spaces = 1;
		int i = 0;
		while (trimmed[i])
		{
			if (trimmed[i] != ' ' && trimmed[i] != '\n' && trimmed[i] != '\t')
			{
				only_spaces = 0;
				break;
			}
			i++;
		}

		if (!map_started && only_spaces)
		{
			free(line);
			continue;
		}

		if (!map_started &&
			(ft_strncmp(trimmed, "NO", 2) == 0 || ft_strncmp(trimmed, "SO", 2) == 0 ||
			 ft_strncmp(trimmed, "WE", 2) == 0 || ft_strncmp(trimmed, "EA", 2) == 0 ||
			 ft_strncmp(trimmed, "F", 1) == 0  || ft_strncmp(trimmed, "C", 1) == 0))
		{
			parse_config_line(trimmed, cfg);
		}
		else
		{
			// After map started, reject empty lines (only spaces)
			if (map_started && only_spaces)
			{
				free(line);
				error("Empty line inside map");
			}
			map_started = 1;
			save_map_line(cfg, line);
		}
		free(line);
	}
	close(fd);

	// Validate required config keys present
	if (!cfg->texture_no || !cfg->texture_so || !cfg->texture_we || !cfg->texture_ea)
		error("Missing texture paths");
	if (cfg->floor_color == -1 || cfg->ceiling_color == -1)
		error("Missing floor or ceiling color");
	if (cfg->floor_color == cfg->ceiling_color)
		error("Floor and ceiling colors must be different");

	validate_map_characters(cfg);

	int width;
	char **padded = pad_map(cfg->map_lines, cfg->map_height, &width);

	check_closed_map(padded, cfg->map_height, width);

	find_player(cfg);

	i = 0;
	while (i < cfg->map_height)
	{
		free(padded[i]);
		i++;
	}
	free(padded);
}

// ---------- MAIN ----------

int main(int ac, char **av)
{
	t_config	cfg;
	int i;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./parser filename", 2);
		return (1);
	}

	ft_bzero(&cfg, sizeof(t_config));
	cfg.floor_color = -1;
	cfg.ceiling_color = -1;
	cfg.map_lines = NULL;
	cfg.map_height = 0;

	parse_file(av[1], &cfg);

	printf("Textures:\nNO: %s\nSO: %s\nWE: %s\nEA: %s\n",
		cfg.texture_no, cfg.texture_so, cfg.texture_we, cfg.texture_ea);
	printf("Floor Color: #%06X\nCeiling Color: #%06X\n",
		cfg.floor_color, cfg.ceiling_color);
	printf("Player at (%.1f, %.1f) facing %c\n",
		cfg.player_x, cfg.player_y, cfg.player_dir);

	free(cfg.texture_no);
	free(cfg.texture_so);
	free(cfg.texture_we);
	free(cfg.texture_ea);

	i = 0;
	while (i < cfg.map_height)
	{
		free(cfg.map_lines[i]);
		i++;
	}
	free(cfg.map_lines);

	return 0;
}
