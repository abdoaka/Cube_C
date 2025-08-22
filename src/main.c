/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:17:53 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/22 15:58:29 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3rd.h"

static void	init_config(t_config *cfg)
{
	ft_bzero(cfg, sizeof(t_config));
	cfg->floor_color = -1;
	cfg->ceiling_color = -1;
	cfg->map_lines = NULL;
	cfg->map_height = 0;
}

int	start_game(t_config *config)
{
	t_game	game;

	init_game(&game, config);
	if (!init_mlx(&game))
	{
		printf("Error: Failed to initialize MLX42\n");
		return (0);
	}
	if (!init_player(&game))
	{
		cleanup_game(&game);
		return (0);
	}
	mlx_loop_hook(game.mlx, handle_input, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_close_hook(game.mlx, close_window, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (1);
}

void system_leaks(void)
{
	system("leaks -q cub3D");
}
int	main(int ac, char **av)
{
	atexit(system_leaks);
	t_config	cfg;
	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./cub3d filename.cub", 2);
		return (1);
	}
	init_config(&cfg);
	parse_file(av[1], &cfg);
	printf("Parsing successful! Player at (%.1f, %.1f)\n",
		cfg.player_x, cfg.player_y);
	printf("Parsed ceiling color: 0x%06X\n", cfg.ceiling_color);
	printf("Parsed floor color: 0x%06X\n", cfg.floor_color);
	if (!start_game(&cfg))
	{
		cleanup_config(&cfg);
		return (1);
	}
	cleanup_config(&cfg);
	return (0);
}
