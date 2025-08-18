#include "../../includes/cub3rd.h"
#include "../includes/rendering.h"

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;
	int	tile_size;

	tile_size = calculate_tile_size(game);
	if (tile_size < 4)
		tile_size = 4;
		
	map_x = (int)(x / tile_size);
	map_y = (int)(y / tile_size);
	
	if (map_y < 0 || map_y >= game->config->map_height)
		return (1);
	if (map_x < 0 || map_x >= (int)strlen(game->config->map_lines[map_y]))
		return (1);
	return (game->config->map_lines[map_y][map_x] == '1');
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2.0 * M_PI);
	if (angle < 0)
		angle += 2.0 * M_PI;
	return (angle);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_horizontal_ray(t_game *game, t_ray *ray, double *h_x, double *h_y)
{
	double	y_intercept;
	double	x_intercept;
	double	y_step;
	double	x_step;
	double	next_x;
	double	next_y;
	int		tile_size;
	int		max_width;
	int		max_height;

	tile_size = calculate_tile_size(game);
	if (tile_size < 4)
		tile_size = 4;
	
	// Calculate map boundaries in pixels
	max_width = 0;
	for (int i = 0; i < game->config->map_height; i++)
	{
		int width = strlen(game->config->map_lines[i]);
		if (width > max_width)
			max_width = width;
	}
	max_width *= tile_size;
	max_height = game->config->map_height * tile_size;

	// Find first horizontal grid line intersection
	y_intercept = floor((game->player.y * tile_size) / tile_size) * tile_size;
	if (sin(ray->angle) > 0)
		y_intercept += tile_size;
	x_intercept = (game->player.x * tile_size) + (y_intercept - (game->player.y * tile_size)) / tan(ray->angle);

	// Calculate step sizes
	y_step = (sin(ray->angle) > 0) ? tile_size : -tile_size;
	x_step = y_step / tan(ray->angle);

	next_x = x_intercept;
	next_y = y_intercept;

	while (next_x >= 0 && next_x < max_width && next_y >= 0 && next_y < max_height)
	{
		// Check for wall hit
		double check_y = next_y;
		if (sin(ray->angle) < 0)  // Ray going up
			check_y -= 1;
			
		if (is_wall(game, next_x, check_y))
		{
			*h_x = next_x / tile_size;  // Convert back to grid units
			*h_y = next_y / tile_size;
			return;
		}
		next_x += x_step;
		next_y += y_step;
	}
	*h_x = -1;
	*h_y = -1;
}

void	cast_single_ray(t_game *game, t_ray *ray)
{
	double	h_x, h_y, v_x, v_y;
	double	h_dist, v_dist;

	ray->angle = normalize_angle(ray->angle);
	
	// Cast both horizontal and vertical rays
	cast_horizontal_ray(game, ray, &h_x, &h_y);
	cast_vertical_ray(game, ray, &v_x, &v_y);
	
	// Calculate distances
	h_dist = (h_x != -1) ? distance_between_points(game->player.x, game->player.y, h_x, h_y) : 9999.0;
	v_dist = (v_x != -1) ? distance_between_points(game->player.x, game->player.y, v_x, v_y) : 9999.0;
	
	// Choose the closer intersection
	if (v_dist < h_dist)
	{
		ray->wall_hit_x = v_x;
		ray->wall_hit_y = v_y;
		ray->distance = v_dist;
		ray->hit_vertical = 1;  // Hit a vertical wall (East/West)
	}
	else
	{
		ray->wall_hit_x = h_x;
		ray->wall_hit_y = h_y;
		ray->distance = h_dist;
		ray->hit_vertical = 0;  // Hit a horizontal wall (North/South)
	}
}

void	cast_vertical_ray(t_game *game, t_ray *ray, double *v_x, double *v_y)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	next_x;
	double	next_y;
	int		tile_size;
	int		max_width;
	int		max_height;

	tile_size = calculate_tile_size(game);
	if (tile_size < 4)
		tile_size = 4;
	
	// Calculate map boundaries in pixels
	max_width = 0;
	for (int i = 0; i < game->config->map_height; i++)
	{
		int width = strlen(game->config->map_lines[i]);
		if (width > max_width)
			max_width = width;
	}
	max_width *= tile_size;
	max_height = game->config->map_height * tile_size;

	// Find first vertical grid line intersection
	x_intercept = floor((game->player.x * tile_size) / tile_size) * tile_size;
	if (cos(ray->angle) > 0)  // Ray going right
		x_intercept += tile_size;
	y_intercept = (game->player.y * tile_size) + (x_intercept - (game->player.x * tile_size)) * tan(ray->angle);

	// Calculate step sizes
	x_step = (cos(ray->angle) > 0) ? tile_size : -tile_size;
	y_step = x_step * tan(ray->angle);

	next_x = x_intercept;
	next_y = y_intercept;

	while (next_x >= 0 && next_x < max_width && next_y >= 0 && next_y < max_height)
	{
		// Check for wall hit
		double check_x = next_x;
		if (cos(ray->angle) < 0)  // Ray going left
			check_x -= 1;
			
		if (is_wall(game, check_x, next_y))
		{
			*v_x = next_x / tile_size;  // Convert back to grid units
			*v_y = next_y / tile_size;
			return;
		}
		next_x += x_step;
		next_y += y_step;
	}
	*v_x = -1;
	*v_y = -1;
}