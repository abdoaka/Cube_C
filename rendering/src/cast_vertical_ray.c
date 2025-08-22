/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical_ray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:56:00 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 18:56:02 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3rd.h"
#include "../includes/rendering.h"

static void	calculate_map_boundaries(t_game *game, t_vertical_ray_data *data)
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

static void	setup_vertical_intercept(t_game *game, t_ray *ray,
		t_vertical_ray_data *data)
{
	data->x_intercept = floor((game->player.x * data->tile_size)
			/ data->tile_size) * data->tile_size;
	if (cos(ray->angle) > 0)
		data->x_intercept += data->tile_size;
	data->y_intercept = (game->player.y * data->tile_size) + (data->x_intercept
			- (game->player.x * data->tile_size)) * tan(ray->angle);
	if (cos(ray->angle) > 0)
		data->x_step = data->tile_size;
	else
		data->x_step = -data->tile_size;
	data->y_step = data->x_step * tan(ray->angle);
	data->next_x = data->x_intercept;
	data->next_y = data->y_intercept;
}

static void step_vertical_ray(t_game *game, t_ray *ray, t_vertical_ray_data *data)
{
    double check_x;

    while (data->next_x >= 0 && data->next_x < data->max_width
        && data->next_y >= 0 && data->next_y < data->max_height)
    {
        check_x = data->next_x;
        if (cos(ray->angle) < 0)
            check_x -= 1;
        if (is_wall(game, check_x, data->next_y))
        {
            data->result_x = data->next_x / data->tile_size;
            data->result_y = data->next_y / data->tile_size;
            data->wall_found = 1;
            return;
        }
        data->next_x += data->x_step;
        data->next_y += data->y_step;
    }
    data->result_x = -1;
    data->result_y = -1;
    data->wall_found = 0;
}

void cast_vertical_ray(t_game *game, t_ray *ray, double *v_x, double *v_y)
{
    t_vertical_ray_data data;

    data.tile_size = calculate_tile_size(game);
    if (data.tile_size < 4)
        data.tile_size = 4;
    calculate_map_boundaries(game, &data);
    setup_vertical_intercept(game, ray, &data);
    step_vertical_ray(game, ray, &data);
    *v_x = data.result_x;
    *v_y = data.result_y;
}
