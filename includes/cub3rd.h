/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3rd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absaadan <absaadan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:18:31 by absaadan          #+#    #+#             */
/*   Updated: 2025/08/21 19:18:34 by absaadan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3RD_H
# define CUB3RD_H

# define _USE_MATH_DEFINES
# include "../mlx/include/MLX42/MLX42.h"
# include "../parsing/cube.h"
# include "../textures/includes/textures.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define FOV 60
# define NUM_RAYS WINDOW_WIDTH

# define MOVE_SPEED 2.0
# define ROT_SPEED 0.05

# define KEY_W MLX_KEY_W
# define KEY_A MLX_KEY_A
# define KEY_S MLX_KEY_S
# define KEY_D MLX_KEY_D
# define KEY_Q MLX_KEY_Q
# define KEY_LEFT MLX_KEY_LEFT
# define KEY_RIGHT MLX_KEY_RIGHT
# define KEY_ESC MLX_KEY_ESCAPE

typedef struct s_player
{
	double		x;
	double		y;
	double		rotation;
}				t_player;

typedef struct s_ray
{
	double		angle;
	double		wall_hit_x;
	double		wall_hit_y;
	double		distance;
	int			hit_vertical;
}				t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_config	*config;
	t_player	player;
	t_ray		*rays;
	t_textures	textures;
}				t_game;

int				main(int argc, char **argv);

int				init_mlx(t_game *game);
int				init_player(t_game *game);
void			init_game(t_game *game, t_config *config);

void			handle_input(void *param);
void			close_window(void *param);
void			game_loop(void *param);

void			cleanup_game(t_game *game);
int				calculate_tile_size(t_game *game);

uint32_t		convert_rgb_to_rgba(int rgb_color);

void			move_player(t_game *game);
void			rotate_player(t_game *game);
int				check_collision(t_game *game, double new_x, double new_y);

#endif
