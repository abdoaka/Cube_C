/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:14:23 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 19:16:15 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3rd.h"
#include "../../rendering/includes/rendering.h"

void	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_close_window(game->mlx);
}

int	check_collision(t_game *game, double new_x, double new_y)
{
	int		tile_size;
	double	player_radius;

	tile_size = calculate_tile_size(game);
	if (tile_size < 4)
		tile_size = 4;
	player_radius = 0.3;
	if (is_wall(game, (new_x + player_radius) * tile_size, (new_y
				+ player_radius) * tile_size))
		return (1);
	if (is_wall(game, (new_x - player_radius) * tile_size, (new_y
				+ player_radius) * tile_size))
		return (1);
	if (is_wall(game, (new_x + player_radius) * tile_size, (new_y
				- player_radius) * tile_size))
		return (1);
	if (is_wall(game, (new_x - player_radius) * tile_size, (new_y
				- player_radius) * tile_size))
		return (1);
	return (0);
}

void	rotate_player(t_game *game)
{
	double	rot_step;

	rot_step = 0.03;
	if (mlx_is_key_down(game->mlx, KEY_LEFT))
		game->player.rotation -= rot_step;
	if (mlx_is_key_down(game->mlx, KEY_RIGHT))
		game->player.rotation += rot_step;
	game->player.rotation = normalize_angle(game->player.rotation);
}

void	handle_input(void *param)
{
	t_game	*game;
	int		x;
	int		y;

	x = 0;
	y = 0;
	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, KEY_ESC) || mlx_is_key_down(game->mlx,
			KEY_Q))
		mlx_close_window(game->mlx);
	move_player(game);
	rotate_player(game);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	game_loop(void *param)
{
	t_game	*game;
	int		y;
	int		x;

	game = (t_game *)param;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(game->image, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	render_3d_view(game);
}
