/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:23:40 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 19:23:43 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/textures.h"

uint32_t	get_texture_pixel(xpm_t *texture, int x, int y)
{
	uint8_t		*pixel_data;
	uint32_t	color;

	if (!texture || x < 0 || y < 0)
		return (0xFF00FFFF);
	if (x >= (int)texture->texture.width || y >= (int)texture->texture.height)
		return (0xFF00FFFF);
	pixel_data = texture->texture.pixels;
	color = *(uint32_t *)(pixel_data + (y * texture->texture.width + x) * 4);
	return (color);
}

uint32_t get_wall_pixel_color(t_game *game, t_ray *ray, int screen_y, t_wall_bounds *bounds)
{
    xpm_t *texture;
    double wall_hit_pos;
    int tex_x;
    int tex_y;
    double tex_pos;

    texture = get_wall_texture(game, ray);
    wall_hit_pos = calculate_wall_hit_position(game, ray);
    tex_x = get_texture_x(texture, wall_hit_pos);
    tex_pos = (double)(screen_y - bounds->top) / (bounds->bottom - bounds->top);
    tex_y = (int)(tex_pos * texture->texture.height);
    if (tex_y < 0)
        tex_y = 0;
    if (tex_y >= (int)texture->texture.height)
        tex_y = texture->texture.height - 1;
    return (get_texture_pixel(texture, tex_x, tex_y));
}
