/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:21:56 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 19:22:05 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include "../../mlx/include/MLX42/MLX42.h"
# include "../../parsing/cube.h"

typedef struct s_game	t_game;
typedef struct s_ray	t_ray;

typedef struct s_textures
{
	xpm_t				*north;
	xpm_t				*south;
	xpm_t				*east;
	xpm_t				*west;
}						t_textures;

int						load_all_textures(t_config *config,
							t_textures *textures);
void					free_all_textures(t_textures *textures);
int						load_single_texture(char *path, xpm_t **texture);
xpm_t					*get_wall_texture(t_game *game, t_ray *ray);
xpm_t					*get_vertical_wall_texture(t_game *game, t_ray *ray);
xpm_t					*get_horizontal_wall_texture(t_game *game, t_ray *ray);
double					calculate_wall_hit_position(t_game *game, t_ray *ray);
int						get_texture_x(xpm_t *texture, double wall_hit_pos);
uint32_t				get_texture_pixel(xpm_t *texture, int x, int y);
uint32_t				get_wall_pixel_color(t_game *game, t_ray *ray, int y,
							int wall_top, int wall_bottom);

#endif
