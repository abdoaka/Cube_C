/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:04:01 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 19:20:37 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3rd.h"
#include "../../textures/includes/textures.h"
#include "../includes/rendering.h"

void	draw_textured_wall_strip(t_game *game, t_ray *ray, int screen_x,
		int strip_width, int wall_top, int wall_bottom)
{
	int				x;
	int				y;
	uint32_t		pixel_color;
	t_wall_bounds	bounds;

	bounds.top = wall_top;
	bounds.bottom = wall_bottom;
	x = screen_x;
	while (x < screen_x + strip_width && x < WINDOW_WIDTH)
	{
		draw_ceiling_floor(game, x, wall_top, wall_bottom);
		y = wall_top;
		while (y < wall_bottom && y < WINDOW_HEIGHT)
		{
			if (y >= 0)
			{
				pixel_color = get_wall_pixel_color(game, ray, y, &bounds);
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
