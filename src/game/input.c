#include "../../includes/cub3rd.h"
#include "../../rendering/includes/rendering.h"

#include "../../includes/cub3rd.h"

int	check_collision(t_game *game, double new_x, double new_y)
{
	int		tile_size;
	double	player_radius;
	
	tile_size = calculate_tile_size(game);
	if (tile_size < 4)
		tile_size = 4;
		
	player_radius = 0.3;  // Small buffer around player
	
	// Check all four corners around the player
	if (is_wall(game, (new_x + player_radius) * tile_size, (new_y + player_radius) * tile_size))
		return (1);
	if (is_wall(game, (new_x - player_radius) * tile_size, (new_y + player_radius) * tile_size))
		return (1);
	if (is_wall(game, (new_x + player_radius) * tile_size, (new_y - player_radius) * tile_size))
		return (1);
	if (is_wall(game, (new_x - player_radius) * tile_size, (new_y - player_radius) * tile_size))
		return (1);
	return (0);
}

void	move_player(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_step;

	move_step = 0.09;  // Much slower movement
	
	// W - Move forward
	if (mlx_is_key_down(game->mlx, KEY_W))
	{
		new_x = game->player.x + cos(game->player.rotation) * move_step;
		new_y = game->player.y + sin(game->player.rotation) * move_step;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	// S - Move backward
	if (mlx_is_key_down(game->mlx, KEY_S))
	{
		new_x = game->player.x - cos(game->player.rotation) * move_step;
		new_y = game->player.y - sin(game->player.rotation) * move_step;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	// A - Strafe left
	if (mlx_is_key_down(game->mlx, KEY_A))
	{
		new_x = game->player.x + cos(game->player.rotation - M_PI/2) * move_step;
		new_y = game->player.y + sin(game->player.rotation - M_PI/2) * move_step;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
	// D - Strafe right
	if (mlx_is_key_down(game->mlx, KEY_D))
	{
		new_x = game->player.x + cos(game->player.rotation + M_PI/2) * move_step;
		new_y = game->player.y + sin(game->player.rotation + M_PI/2) * move_step;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.x = new_x;
			game->player.y = new_y;
		}
	}
}

void	rotate_player(t_game *game)
{
	double rot_step = 0.03;  // Slower rotation
	
	if (mlx_is_key_down(game->mlx, KEY_LEFT))
		game->player.rotation -= rot_step;
	if (mlx_is_key_down(game->mlx, KEY_RIGHT))
		game->player.rotation += rot_step;
		
	game->player.rotation = normalize_angle(game->player.rotation);
}

void	handle_input(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, KEY_ESC))
		mlx_close_window(game->mlx);
	
	move_player(game);
	rotate_player(game);
	
	// Clear screen with black (3D view area)
	// We'll add 3D rendering here later
	int x = 0, y = 0;
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


void game_loop(void *param)
{
    t_game *game;
    game = (t_game *)param;
    
    // Clear the screen with black
    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            mlx_put_pixel(game->image, x, y, 0x000000FF);
        }
    }
    
    // Render 3D view (replaces the 2D map/rays/player)
    render_3d_view(game);
    
    // Draw minimap overlay (always visible)
    draw_minimap(game);
    draw_minimap_player(game);
}