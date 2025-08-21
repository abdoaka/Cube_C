#include "../../includes/cub3rd.h"
#include "../includes/rendering.h"
#include "../../textures/includes/textures.h"

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

// Replace your draw_wall_strip function in render_3d.c with this:

void	draw_wall_strip(t_game *game, double ray_angle, int screen_x, 
	int strip_width, double projection_distance)
{
	t_ray		ray;
	double		corrected_distance;
	double		wall_height;
	int			wall_top;
	int			wall_bottom;

	ray.angle = ray_angle;
	cast_single_ray(game, &ray);
	corrected_distance = ray.distance * cos(ray_angle - game->player.rotation);
	wall_height = (1.0 / corrected_distance) * projection_distance;
	wall_top = (WINDOW_HEIGHT - (int)wall_height) / 2;
	wall_bottom = (WINDOW_HEIGHT + (int)wall_height) / 2;
	draw_textured_wall_strip(game, &ray, screen_x, strip_width, wall_top, 
		wall_bottom);
}

void	draw_textured_wall_strip(t_game *game, t_ray *ray, int screen_x, 
	int strip_width, int wall_top, int wall_bottom)
{
	int			x;
	int			y;
	uint32_t	pixel_color;

	x = screen_x;
	while (x < screen_x + strip_width && x < WINDOW_WIDTH)
	{
		draw_ceiling_floor(game, x, wall_top, wall_bottom);
		y = wall_top;
		while (y < wall_bottom && y < WINDOW_HEIGHT)
		{
			if (y >= 0)
			{
				pixel_color = get_wall_pixel_color(game, ray, y, wall_top, 
					wall_bottom);
				mlx_put_pixel(game->image, x, y, pixel_color);
			}
			y++;
		}
		x++;
	}
}

void	draw_ceiling_floor(t_game *game, int x, int wall_top, int wall_bottom)
{
	int			y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	ceiling_color = convert_rgb_to_rgba(game->config->ceiling_color);
	floor_color = convert_rgb_to_rgba(game->config->floor_color);
	
	y = 0;
	while (y < wall_top && y < WINDOW_HEIGHT)
	{
		mlx_put_pixel(game->image, x, y, ceiling_color);
		y++;
	}
	y = wall_bottom;
	while (y < WINDOW_HEIGHT)
	{
		if (y >= 0)
			mlx_put_pixel(game->image, x, y, floor_color);
		y++;
	}
}