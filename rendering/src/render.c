/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:56:38 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 18:56:41 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3rd.h"
#include "../includes/rendering.h"

int	calculate_tile_size(t_game *game)
{
	int	max_width;
	int	row;
	int	current_width;
	int	tile_size_w;
	int	tile_size_h;

	max_width = 0;
	row = 0;
	while (row < game->config->map_height)
	{
		current_width = strlen(game->config->map_lines[row]);
		if (current_width > max_width)
			max_width = current_width;
		row++;
	}
	tile_size_w = (WINDOW_WIDTH - 40) / max_width;
	tile_size_h = (WINDOW_HEIGHT - 40) / game->config->map_height;
	if (tile_size_w < tile_size_h)
		return (tile_size_w);
	else
		return (tile_size_h);
}
