#include "../../includes/cub3rd.h"
#include "../includes/rendering.h"

void	render_3d_view(t_game *game)
{
	int		ray_count;
	int		ray_index;
	double	projection_distance;
	double	fov_radians;
	double	angle_step;
	double	ray_angle;
	int		strip_width;

	// Performance settings
	ray_count = WINDOW_WIDTH / 4;  // 256 rays for 1024px width
	strip_width = 4;  // Each ray covers 4 pixel columns
	
	// Calculate projection distance (like your JS)
	fov_radians = FOV * M_PI / 180.0;
	projection_distance = (WINDOW_WIDTH / 2.0) / tan(fov_radians / 2.0);
	
	// Calculate angle step between rays
	angle_step = fov_radians / ray_count;
	
	ray_index = 0;
	while (ray_index < ray_count)
	{
		// Calculate ray angle
		ray_angle = game->player.rotation - (fov_radians / 2.0) + (ray_index * angle_step);
		
		// Cast ray and draw wall strip
		draw_wall_strip(game, ray_angle, ray_index * strip_width, strip_width, projection_distance);
		
		ray_index++;
	}
}

void	draw_wall_strip(t_game *game, double ray_angle, int screen_x, int strip_width, double projection_distance)
{
	t_ray	ray;
	double	corrected_distance;
	double	wall_height;
	int		wall_top;
	int		wall_bottom;
	uint32_t wall_color;
	int		x;
	int		y;

	// Cast the ray
	ray.angle = ray_angle;
	cast_single_ray(game, &ray);
	
	// Apply fisheye correction
	corrected_distance = ray.distance * cos(ray_angle - game->player.rotation);
	
	// Calculate wall height (like your JS wallstripheight)
	wall_height = (1.0 / corrected_distance) * projection_distance;  // Using 1.0 as tile_size
	
	// Calculate wall boundaries on screen
	wall_top = (WINDOW_HEIGHT - (int)wall_height) / 2;
	wall_bottom = (WINDOW_HEIGHT + (int)wall_height) / 2;
	
	// Choose wall color based on direction
	if (ray.hit_vertical)
		wall_color = 0xFF0000FF;  // Red for vertical walls (E/W)
	else
		wall_color = 0x0000FFFF;  // Blue for horizontal walls (N/S)
	
	// Draw the wall strip
	x = screen_x;
	while (x < screen_x + strip_width && x < WINDOW_WIDTH)
	{
		// Draw ceiling (dark gray)
		y = 0;
		while (y < wall_top && y < WINDOW_HEIGHT)
		{
			mlx_put_pixel(game->image, x, y, 0x333333FF);
			y++;
		}
		
		// Draw wall
		y = wall_top;
		while (y < wall_bottom && y < WINDOW_HEIGHT)
		{
			if (y >= 0)
				mlx_put_pixel(game->image, x, y, wall_color);
			y++;
		}
		
		// Draw floor (light gray)
		y = wall_bottom;
		while (y < WINDOW_HEIGHT)
		{
			if (y >= 0)
				mlx_put_pixel(game->image, x, y, 0xCCCCCCFF);
			y++;
		}
		x++;
	}
}