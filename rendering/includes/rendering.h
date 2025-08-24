/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:55:43 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 18:55:45 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include <math.h>

typedef struct s_game	t_game;
typedef struct s_ray	t_ray;

typedef struct s_horizontal_ray_data
{
	double				y_intercept;
	double				x_intercept;
	double				y_step;
	double				x_step;
	double				next_x;
	double				next_y;
	int					tile_size;
	int					max_width;
	int					max_height;
	double				result_x;
	double				result_y;
	int					wall_found;
}						t_horizontal_ray_data;

typedef struct s_vertical_ray_data
{
	double				x_intercept;
	double				y_intercept;
	double				x_step;
	double				y_step;
	double				next_x;
	double				next_y;
	int					tile_size;
	int					max_width;
	int					max_height;
	double				result_x;
	double				result_y;
	int					wall_found;
}						t_vertical_ray_data;

typedef struct s_ray_intersection
{
	double				x;
	double				y;
	double				distance;
}						t_ray_intersection;

typedef struct s_wall_strip_params
{
	int					screen_x;
	int					strip_width;
	int					wall_top;
	int					wall_bottom;
}						t_wall_strip_params;

typedef struct s_render_data
{
	int					ray_count;
	int					strip_width;
	double				projection_distance;
	double				fov_radians;
	double				angle_step;
}						t_render_data;

typedef struct s_strip_render_params
{
	double				ray_angle;
	int					screen_x;
	int					strip_width;
	double				projection_distance;
}						t_strip_render_params;

int						is_wall(t_game *game, double x, double y);
double					normalize_angle(double angle);
double					distance_between_points(double x1, double y1, double x2,
							double y2);
void					cast_horizontal_ray(t_game *game, t_ray *ray,
							double *h_x, double *h_y);
void					cast_vertical_ray(t_game *game, t_ray *ray, double *v_x,
							double *v_y);
void					cast_single_ray(t_game *game, t_ray *ray);

void					render_frame(t_game *game);
void					render_3d_view(t_game *game);
void					draw_wall_strip(t_game *game,
							t_strip_render_params *params);

void					draw_textured_wall_strip(t_game *game, t_ray *ray,
							t_wall_strip_params *params);
void					draw_ceiling_floor(t_game *game, int x, int wall_top,
							int wall_bottom);
size_t					ft_strlen(const char *s);

#endif
