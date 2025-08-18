#include "../../includes/cub3rd.h"
#include "../includes/rendering.h"

int	calculate_tile_size(t_game *game)
{
	int	max_width;
	int	row;
	int	current_width;
	int	tile_size_w;
	int	tile_size_h;

	// Find the maximum width of the map
	max_width = 0;
	row = 0;
	while (row < game->config->map_height)
	{
		current_width = strlen(game->config->map_lines[row]);
		if (current_width > max_width)
			max_width = current_width;
		row++;
	}

	// Calculate tile size to fit the entire map in the window
	// Leave some margin (subtract 40 pixels for borders)
	tile_size_w = (WINDOW_WIDTH - 40) / max_width;
	tile_size_h = (WINDOW_HEIGHT - 40) / game->config->map_height;

	// Use the smaller of the two to ensure it fits both dimensions
	if (tile_size_w < tile_size_h)
		return (tile_size_w);
	else
		return (tile_size_h);
}

void	draw_2d_map(t_game *game)
{
	int		row;
	int		col;
	int		tile_x;
	int		tile_y;
	int		x;
	int		y;
	uint32_t	color;
	int		tile_size;

	tile_size = calculate_tile_size(game);
	// Minimum tile size for visibility
	if (tile_size < 4)
		tile_size = 4;
		
	row = 0;
	while (row < game->config->map_height)
	{
		col = 0;
		while (col < (int)strlen(game->config->map_lines[row]))
		{
			tile_x = col * tile_size;
			tile_y = row * tile_size;
			if (game->config->map_lines[row][col] == '1')
				color = 0x444444FF;  // Dark gray for walls
			else
				color = 0xCCCCCCFF;  // Light gray for empty space
			
			// Fill the tile
			y = tile_y + 1;  // Start 1 pixel in for grid lines
			while (y < tile_y + tile_size - 1)  // End 1 pixel before for grid lines
			{
				x = tile_x + 1;
				while (x < tile_x + tile_size - 1)
				{
					if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
						mlx_put_pixel(game->image, x, y, color);
					x++;
				}
				y++;
			}
			
			// Draw grid borders (black lines)
			// Top border
			x = tile_x;
			while (x < tile_x + tile_size && x < WINDOW_WIDTH)
			{
				if (tile_y < WINDOW_HEIGHT)
					mlx_put_pixel(game->image, x, tile_y, 0x000000FF);
				x++;
			}
			// Left border
			y = tile_y;
			while (y < tile_y + tile_size && y < WINDOW_HEIGHT)
			{
				if (tile_x < WINDOW_WIDTH)
					mlx_put_pixel(game->image, tile_x, y, 0x000000FF);
				y++;
			}
			col++;
		}
		row++;
	}
}

void	draw_circle(t_game *game, int center_x, int center_y, int radius, uint32_t color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			dx = x - center_x;
			dy = y - center_y;
			if (dx * dx + dy * dy <= radius * radius)
			{
				if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
					mlx_put_pixel(game->image, x, y, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_player(t_game *game)
{
	int		center_x;
	int		center_y;
	int		line_end_x;
	int		line_end_y;
	int		line_length;
	int		tile_size;

	tile_size = calculate_tile_size(game);
	if (tile_size < 4)
		tile_size = 4;
		
	// Fix: Multiply directly by tile_size (player coords are already in "grid units")
	center_x = (int)(game->player.x * tile_size);
	center_y = (int)(game->player.y * tile_size);
	line_length = tile_size / 3;  // Make line length proportional to tile size
	
	line_end_x = center_x + (int)(cos(game->player.rotation) * line_length);
	line_end_y = center_y + (int)(sin(game->player.rotation) * line_length);
	
	// Make circle radius proportional to tile size
	int player_radius = tile_size / 8;
	if (player_radius < 2)
		player_radius = 2;
		
	draw_circle(game, center_x, center_y, player_radius, 0xFF0000FF);
	draw_line(game, center_x, center_y, line_end_x, line_end_y, 0x0000FFFF);
}

void	draw_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		if (x0 >= 0 && x0 < WINDOW_WIDTH && y0 >= 0 && y0 < WINDOW_HEIGHT)
			mlx_put_pixel(game->image, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_rays(t_game *game)
{
	t_ray	ray;
	int		i;
	int		tile_size;
	int		player_screen_x;
	int		player_screen_y;
	int		ray_end_x;
	int		ray_end_y;
	double	angle_step;
	
	tile_size = calculate_tile_size(game);
	if (tile_size < 4)
		tile_size = 4;
		
	player_screen_x = (int)(game->player.x * tile_size);
	player_screen_y = (int)(game->player.y * tile_size);
	
	// Cast multiple rays for visualization
	angle_step = (M_PI / 3.0) / 60.0;  // 60 degree FOV divided by 60 rays
	
	for (i = 0; i < 60; i++)
	{
		ray.angle = game->player.rotation - (M_PI / 6.0) + (i * angle_step);
		cast_single_ray(game, &ray);
		
		if (ray.distance < 9999.0)
		{
			ray_end_x = (int)(ray.wall_hit_x * tile_size);
			ray_end_y = (int)(ray.wall_hit_y * tile_size);
			draw_line(game, player_screen_x, player_screen_y, ray_end_x, ray_end_y, 0xFF0000FF);
		}
	}
}