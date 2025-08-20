#include "../includes/textures.h"
#include "../../includes/cub3rd.h"
#include <math.h>

xpm_t	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->hit_vertical)
		return (get_vertical_wall_texture(game, ray));
	else
		return (get_horizontal_wall_texture(game, ray));
}

xpm_t	*get_vertical_wall_texture(t_game *game, t_ray *ray)
{
	if (cos(ray->angle) > 0)
		return (game->textures.east);
	else
		return (game->textures.west);
}

xpm_t	*get_horizontal_wall_texture(t_game *game, t_ray *ray)
{
	if (sin(ray->angle) > 0)
		return (game->textures.south);
	else
		return (game->textures.north);
}

double	calculate_wall_hit_position(t_game *game, t_ray *ray)
{
	double	wall_hit_pos;

	if (ray->hit_vertical)
		wall_hit_pos = game->player.y + ray->distance * sin(ray->angle);
	else
		wall_hit_pos = game->player.x + ray->distance * cos(ray->angle);
	wall_hit_pos = wall_hit_pos - floor(wall_hit_pos);
	return (wall_hit_pos);
}

int	get_texture_x(xpm_t *texture, double wall_hit_pos)
{
	int	tex_x;

	tex_x = (int)(wall_hit_pos * texture->texture.width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->texture.width)
		tex_x = texture->texture.width - 1;
	return (tex_x);
}