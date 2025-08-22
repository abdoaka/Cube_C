/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:08:06 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 19:11:45 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3rd.h"
#include "../../rendering/includes/rendering.h"
#include "../../textures/includes/textures.h"

int	init_mlx(t_game *game)
{
	mlx_set_setting(MLX_DECORATED, true);
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (0);
	game->image = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->image)
	{
		mlx_terminate(game->mlx);
		return (0);
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) == -1)
	{
		mlx_terminate(game->mlx);
		return (0);
	}
	if (!load_all_textures(game->config, &game->textures))
	{
		printf("Failed to load textures\n");
		return (0);
	}
	return (1);
}

double	convert_player_dir(char dir)
{
	if (dir == 'N')
		return (3.0 * M_PI / 2.0);
	else if (dir == 'S')
		return (M_PI / 2.0);
	else if (dir == 'E')
		return (0.0);
	else if (dir == 'W')
		return (M_PI);
	return (0.0);
}

int	init_player(t_game *game)
{
	game->player.x = game->config->player_x;
	game->player.y = game->config->player_y;
	game->player.rotation = convert_player_dir(game->config->player_dir);
	return (1);
}

void	init_game(t_game *game, t_config *config)
{
	game->config = config;
	game->mlx = NULL;
	game->image = NULL;
}

void	cleanup_game(t_game *game)
{
	if (game && game->textures)
		free_all_textures(game->textures);
}
