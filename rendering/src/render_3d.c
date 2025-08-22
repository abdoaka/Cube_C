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
	t_render_data			data;
	t_strip_render_params	strip_params;
	int						ray_index;

	data.ray_count = WINDOW_WIDTH / 4;
	data.strip_width = 4;
	data.fov_radians = FOV * M_PI / 180.0;
	data.projection_distance = (WINDOW_WIDTH / 2.0) / tan(data.fov_radians
			/ 2.0);
	data.angle_step = data.fov_radians / data.ray_count;
	ray_index = 0;
	while (ray_index < data.ray_count)
	{
		strip_params.ray_angle = game->player.rotation - (data.fov_radians
				/ 2.0) + (ray_index * data.angle_step);
		strip_params.screen_x = ray_index * data.strip_width;
		strip_params.strip_width = data.strip_width;
		strip_params.projection_distance = data.projection_distance;
		draw_wall_strip(game, &strip_params);
		ray_index++;
	}
}

void	draw_wall_strip(t_game *game, t_strip_render_params *params)
{
	t_ray				ray;
	t_wall_strip_params	wall_params;
	double				corrected_distance;
	double				wall_height;

	ray.angle = params->ray_angle;
	cast_single_ray(game, &ray);
	corrected_distance = ray.distance * cos(params->ray_angle
			- game->player.rotation);
	wall_height = (1.0 / corrected_distance) * params->projection_distance;
	wall_params.screen_x = params->screen_x;
	wall_params.strip_width = params->strip_width;
	wall_params.wall_top = (WINDOW_HEIGHT - (int)wall_height) / 2;
	wall_params.wall_bottom = (WINDOW_HEIGHT + (int)wall_height) / 2;
	draw_textured_wall_strip(game, &ray, &wall_params);
}
