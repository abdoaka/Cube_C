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

static double calculate_ray_distance(t_game *game, double x, double y)
{
    if (x != -1)
        return (distance_between_points(game->player.x, game->player.y, x, y));
    return (9999.0);
}

void cast_single_ray(t_game *game, t_ray *ray)
{
    t_ray_intersection horizontal;
    t_ray_intersection vertical;

    ray->angle = normalize_angle(ray->angle);
    cast_horizontal_ray(game, ray, &horizontal.x, &horizontal.y);
    cast_vertical_ray(game, ray, &vertical.x, &vertical.y);
    horizontal.distance = calculate_ray_distance(game, horizontal.x, horizontal.y);
    vertical.distance = calculate_ray_distance(game, vertical.x, vertical.y);
    if (vertical.distance < horizontal.distance)
    {
        ray->wall_hit_x = vertical.x;
        ray->wall_hit_y = vertical.y;
        ray->distance = vertical.distance;
        ray->hit_vertical = 1;
    }
    else
    {
        ray->wall_hit_x = horizontal.x;
        ray->wall_hit_y = horizontal.y;
        ray->distance = horizontal.distance;
        ray->hit_vertical = 0;
    }
}
