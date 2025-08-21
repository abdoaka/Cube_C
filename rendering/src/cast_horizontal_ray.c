/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal_ray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:55:52 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 18:55:54 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3rd.h"
#include "../includes/rendering.h"

static void	calculate_map_boundaries(t_game *game, t_horizontal_ray_data *data)
{
	int	i;
	int	width;

	data->max_width = 0;
	i = 0;
	while (i < game->config->map_height)
	{
		width = strlen(game->config->map_lines[i]);
		if (width > data->max_width)
			data->max_width = width;
		i++;
	}
	data->max_width *= data->tile_size;
	data->max_height = game->config->map_height * data->tile_size;
}

static void	setup_horizontal_intercept(t_game *game, t_ray *ray,
		t_horizontal_ray_data *data)
{
	data->y_intercept = floor((game->player.y * data->tile_size)
			/ data->tile_size) * data->tile_size;
	if (sin(ray->angle) > 0)
		data->y_intercept += data->tile_size;
	data->x_intercept = (game->player.x * data->tile_size) + (data->y_intercept
			- (game->player.y * data->tile_size)) / tan(ray->angle);
	if (sin(ray->angle) > 0)
		data->y_step = data->tile_size;
	else
		data->y_step = -data->tile_size;
	data->x_step = data->y_step / tan(ray->angle);
	data->next_x = data->x_intercept;
	data->next_y = data->y_intercept;
}

static int	step_horizontal_ray(t_game *game, t_ray *ray,
		t_horizontal_ray_data *data, double *h_x, double *h_y)
{
	double	check_y;

	while (data->next_x >= 0 && data->next_x < data->max_width
		&& data->next_y >= 0 && data->next_y < data->max_height)
	{
		check_y = data->next_y;
		if (sin(ray->angle) < 0)
			check_y -= 1;
		if (is_wall(game, data->next_x, check_y))
		{
			*h_x = data->next_x / data->tile_size;
			*h_y = data->next_y / data->tile_size;
			return (1);
		}
		data->next_x += data->x_step;
		data->next_y += data->y_step;
	}
	return (0);
}

void	cast_horizontal_ray(t_game *game, t_ray *ray, double *h_x, double *h_y)
{
	t_horizontal_ray_data	data;

	data.tile_size = calculate_tile_size(game);
	if (data.tile_size < 4)
		data.tile_size = 4;
	calculate_map_boundaries(game, &data);
	setup_horizontal_intercept(game, ray, &data);
	if (step_horizontal_ray(game, ray, &data, h_x, h_y))
		return ;
	*h_x = -1;
	*h_y = -1;
}
