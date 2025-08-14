/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 02:09:07 by marvin            #+#    #+#             */
/*   Updated: 2025/08/14 02:09:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	find_player(t_config *cfg)
{
	int	y;
	int	x;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (cfg->map_lines[y][x])
		{
			if (cfg->map_lines[y][x] == 'N' || cfg->map_lines[y][x] == 'S' ||
				cfg->map_lines[y][x] == 'E' || cfg->map_lines[y][x] == 'W')
			{
				cfg->player_x = x + 0.5f;
				cfg->player_y = y + 0.5f;
				cfg->player_dir = cfg->map_lines[y][x];
				cfg->map_lines[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	error("Player not found");
}
