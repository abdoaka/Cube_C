#ifndef CUB3RD_H
# define CUB3RD_H

# define _USE_MATH_DEFINES
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../mlx/include/MLX42/MLX42.h"
# include "../parsing/cube.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/* Window constants */
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define FOV 60
# define NUM_RAYS WINDOW_WIDTH

/* Player movement constants */
# define MOVE_SPEED 2.0
# define ROT_SPEED 0.05

/* Key codes for MLX42 */
# define KEY_W MLX_KEY_W
# define KEY_A MLX_KEY_A  
# define KEY_S MLX_KEY_S
# define KEY_D MLX_KEY_D
# define KEY_LEFT MLX_KEY_LEFT
# define KEY_RIGHT MLX_KEY_RIGHT
# define KEY_ESC MLX_KEY_ESCAPE

/* Player structure */
typedef struct s_player
{
	double	x;
	double	y;
	double	rotation;
}	t_player;

typedef struct s_ray
{
	double	angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		hit_vertical;	// 1 if hit vertical wall, 0 if horizontal
}	t_ray;

/* Main game structure */
typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_config	*config;
	t_player	player;
	t_ray		*rays;		// Array of rays
}	t_game;

/* Function prototypes - organized by file */
/* src/main.c */
int		main(int argc, char **argv);

/* src/game/init.c - NEW FILE NEEDED */
int		init_mlx(t_game *game);
int		init_player(t_game *game);
void	init_game(t_game *game, t_config *config);

/* src/game/input.c */
void	handle_input(void *param);
void	game_loop(void *param);
void	game_loop(void *param);

/* src/utils/cleanup.c */
void	cleanup_game(t_game *game);
void	draw_rays(t_game *game);
int	calculate_tile_size(t_game *game);
/* src/game/input.c */
void	move_player(t_game *game);
void	rotate_player(t_game *game);
void	handle_input(void *param);
int	check_collision(t_game *game, double new_x, double new_y);
#endif