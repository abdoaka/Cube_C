/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:56:28 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 19:04:23 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3rd.h"
#include "../../textures/includes/textures.h"
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

	ray_count = WINDOW_WIDTH / 4;
	strip_width = 4;
	fov_radians = FOV * M_PI / 180.0;
	projection_distance = (WINDOW_WIDTH / 2.0) / tan(fov_radians / 2.0);
	angle_step = fov_radians / ray_count;
	ray_index = 0;
	while (ray_index < ray_count)
	{
		ray_angle = game->player.rotation - (fov_radians / 2.0) + (ray_index
				* angle_step);
		draw_wall_strip(game, ray_angle, ray_index * strip_width, strip_width,
			projection_distance);
		ray_index++;
	}
}

void	draw_wall_strip(t_game *game, double ray_angle, int screen_x,
		int strip_width, double projection_distance)
{
	t_ray	ray;
	double	corrected_distance;
	double	wall_height;
	int		wall_top;
	int		wall_bottom;

	ray.angle = ray_angle;
	cast_single_ray(game, &ray);
	corrected_distance = ray.distance * cos(ray_angle - game->player.rotation);
	wall_height = (1.0 / corrected_distance) * projection_distance;
	wall_top = (WINDOW_HEIGHT - (int)wall_height) / 2;
	wall_bottom = (WINDOW_HEIGHT + (int)wall_height) / 2;
	draw_textured_wall_strip(game, &ray, screen_x, strip_width, wall_top,
		wall_bottom);
}
