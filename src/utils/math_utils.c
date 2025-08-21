/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:17:32 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 19:17:35 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3rd.h"
#include <stdint.h>

uint32_t	convert_rgb_to_rgba(int rgb_color)
{
	int	r;
	int	g;
	int	b;

	r = (rgb_color >> 16) & 0xFF;
	g = (rgb_color >> 8) & 0xFF;
	b = rgb_color & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}
