#include "../../includes/cub3rd.h"
#include "../includes/rendering.h"

void	draw_minimap(t_game *game)
{
	int		minimap_size;
	int		minimap_x;
	int		minimap_y;
	int		tile_size;
	int		row;
	int		col;
	int		tile_x;
	int		tile_y;
	int		x;
	int		y;
	uint32_t	color;
	int		max_map_width;

	// Minimap settings
	minimap_size = 200;  // 200x200 pixel minimap
	minimap_x = WINDOW_WIDTH - minimap_size - 20;  // 20px from right edge
	minimap_y = 20;  // 20px from top edge
	
	// Calculate max map width
	max_map_width = 0;
	for (int i = 0; i < game->config->map_height; i++)
	{
		int width = strlen(game->config->map_lines[i]);
		if (width > max_map_width)
			max_map_width = width;
	}
	
	// Calculate tile size to fit both width and height
	int tile_size_w = minimap_size / max_map_width;
	int tile_size_h = minimap_size / game->config->map_height;
	tile_size = (tile_size_w < tile_size_h) ? tile_size_w : tile_size_h;
	if (tile_size < 2)
		tile_size = 2;  // Minimum size

	// Draw minimap background (semi-transparent black border)
	y = minimap_y - 5;
	while (y < minimap_y + minimap_size + 5)
	{
		x = minimap_x - 5;
		while (x < minimap_x + minimap_size + 5)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				mlx_put_pixel(game->image, x, y, 0x000000AA);  // Semi-transparent black
			x++;
		}
		y++;
	}

	// Draw map tiles
	row = 0;
	while (row < game->config->map_height)
	{
		col = 0;
		while (col < (int)strlen(game->config->map_lines[row]))
		{
			tile_x = minimap_x + (col * tile_size);
			tile_y = minimap_y + (row * tile_size);
			
			if (game->config->map_lines[row][col] == '1')
				color = 0x444444FF;  // Dark gray for walls
			else
				color = 0xCCCCCCFF;  // Light gray for empty space
			
			// Fill the tile (smaller, no grid lines for minimap)
			y = tile_y;
			while (y < tile_y + tile_size)
			{
				x = tile_x;
				while (x < tile_x + tile_size)
				{
					if (x >= minimap_x && x < minimap_x + minimap_size && 
						y >= minimap_y && y < minimap_y + minimap_size)
						mlx_put_pixel(game->image, x, y, color);
					x++;
				}
				y++;
			}
			col++;
		}
		row++;
	}
}

void	draw_minimap_player(t_game *game)
{
	int		minimap_size;
	int		minimap_x;
	int		minimap_y;
	int		tile_size;
	int		player_x;
	int		player_y;
	int		line_end_x;
	int		line_end_y;
	int		max_map_width;

	minimap_size = 200;
	minimap_x = WINDOW_WIDTH - minimap_size - 20;
	minimap_y = 20;
	
	// Calculate max map width (same logic as in draw_minimap)
	max_map_width = 0;
	for (int i = 0; i < game->config->map_height; i++)
	{
		int width = strlen(game->config->map_lines[i]);
		if (width > max_map_width)
			max_map_width = width;
	}
	
	// Use the same tile size calculation as in draw_minimap
	int tile_size_w = minimap_size / max_map_width;
	int tile_size_h = minimap_size / game->config->map_height;
	tile_size = (tile_size_w < tile_size_h) ? tile_size_w : tile_size_h;
	if (tile_size < 2)
		tile_size = 2;

	// Calculate player position in minimap (with bounds checking)
	player_x = minimap_x + (int)(game->player.x * tile_size);
	player_y = minimap_y + (int)(game->player.y * tile_size);
	
	// Clamp player position to minimap boundaries
	if (player_x < minimap_x)
		player_x = minimap_x;
	if (player_x > minimap_x + minimap_size)
		player_x = minimap_x + minimap_size;
	if (player_y < minimap_y)
		player_y = minimap_y;
	if (player_y > minimap_y + minimap_size)
		player_y = minimap_y + minimap_size;
	
	// Direction line (with bounds checking)
	line_end_x = player_x + (int)(cos(game->player.rotation) * 10);
	line_end_y = player_y + (int)(sin(game->player.rotation) * 10);
	
	// Clamp direction line to minimap boundaries
	if (line_end_x < minimap_x)
		line_end_x = minimap_x;
	if (line_end_x > minimap_x + minimap_size)
		line_end_x = minimap_x + minimap_size;
	if (line_end_y < minimap_y)
		line_end_y = minimap_y;
	if (line_end_y > minimap_y + minimap_size)
		line_end_y = minimap_y + minimap_size;
	
	// Draw player (red dot)
	draw_circle(game, player_x, player_y, 3, 0xFF0000FF);
	
	// Draw direction line (blue)
	draw_line(game, player_x, player_y, line_end_x, line_end_y, 0x0000FFFF);
}