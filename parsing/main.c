/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:47:40 by marvin            #+#    #+#             */
/*   Updated: 2025/08/14 02:47:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_config(t_config *cfg)
{
	ft_bzero(cfg, sizeof(t_config));
	cfg->floor_color = -1;
	cfg->ceiling_color = -1;
	cfg->map_lines = NULL;
	cfg->map_height = 0;
}

static void	print_config(t_config *cfg)
{
	printf("Textures:\nNO: %s\nSO: %s\nWE: %s\nEA: %s\n",
		cfg->texture_no, cfg->texture_so, cfg->texture_we, cfg->texture_ea);
	printf("Floor Color: #%06X\nCeiling Color: #%06X\n",
		cfg->floor_color, cfg->ceiling_color);
	printf("Player at (%.1f, %.1f) facing %c\n",
		cfg->player_x, cfg->player_y, cfg->player_dir);
}

static void	free_config(t_config *cfg)
{
	int	i;

	free(cfg->texture_no);
	free(cfg->texture_so);
	free(cfg->texture_we);
	free(cfg->texture_ea);
	i = 0;
	while (i < cfg->map_height)
		free(cfg->map_lines[i++]);
	free(cfg->map_lines);
}

int	main(int ac, char **av)
{
	t_config	cfg;

	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./parser filename", 2);
		return (1);
	}
	init_config(&cfg);
	parse_file(av[1], &cfg);
	print_config(&cfg);
	free_config(&cfg);
	return (0);
}
