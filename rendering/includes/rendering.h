#ifndef RENDERING_H
# define RENDERING_H

# include <math.h>

/* Forward declarations */
typedef struct s_game t_game;
typedef struct s_ray t_ray;

/* Raycasting functions */
int		is_wall(t_game *game, double x, double y);
double	normalize_angle(double angle);
double	distance_between_points(double x1, double y1, double x2, double y2);
void	cast_horizontal_ray(t_game *game, t_ray *ray, double *h_x, double *h_y);
void	cast_vertical_ray(t_game *game, t_ray *ray, double *v_x, double *v_y);
void	cast_single_ray(t_game *game, t_ray *ray);
void	draw_2d_map(t_game *game);
void	draw_rays(t_game *game);
/* Rendering functions */
void	render_frame(t_game *game);
void	draw_player(t_game *game);
void	draw_line(t_game *game, int x0, int y0, int x1, int y1, uint32_t color);
void	draw_circle(t_game *game, int center_x, int center_y, int radius, uint32_t color);
void	cast_vertical_ray(t_game *game, t_ray *ray, double *v_x, double *v_y);
void	draw_minimap(t_game *game);
void	draw_minimap_player(t_game *game);
void	render_3d_view(t_game *game);
void	draw_wall_strip(t_game *game, double ray_angle, int screen_x, int strip_width, double projection_distance);
#endif