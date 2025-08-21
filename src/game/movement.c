#include "../../includes/cub3rd.h"
#include "../../rendering/includes/rendering.h"

static void try_move_player(t_game *game, double angle_offset, double move_step, int direction)
{
    double new_x;
    double new_y;
    double movement_angle;

    movement_angle = game->player.rotation + angle_offset;
    new_x = game->player.x + (direction * cos(movement_angle) * move_step);
    new_y = game->player.y + (direction * sin(movement_angle) * move_step);
    if (!check_collision(game, new_x, new_y))
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

void move_player(t_game *game)
{
    double move_step;

    move_step = 0.09;
    if (mlx_is_key_down(game->mlx, KEY_W))
        try_move_player(game, 0.0, move_step, 1);
    if (mlx_is_key_down(game->mlx, KEY_S))
        try_move_player(game, 0.0, move_step, -1);
    if (mlx_is_key_down(game->mlx, KEY_A))
        try_move_player(game, -M_PI/2, move_step, 1);
    if (mlx_is_key_down(game->mlx, KEY_D))
        try_move_player(game, M_PI/2, move_step, 1);
}
