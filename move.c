#include "cub.h"

int	move_front(t_game *game)
{
	double	b_x;
	double	b_y;

	b_x = round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view)));
	b_y = round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view)));
	if (game->key[119])
	{
		if (!is_wall(game, game->px + b_x, game->py + b_y))
		{
			b_x = round(MOVE_SPEED * cos(rad(game->view + 30)));
			b_y = round(MOVE_SPEED * sin(rad(game->view + 30)));
			if (!is_wall(game, game->px + b_x, game->py + b_y))
			{
				b_x = round(MOVE_SPEED * cos(rad(game->view - 30)));
				b_y = round(MOVE_SPEED * sin(rad(game->view - 30)));
				if (!is_wall(game, game->px + b_x, game->py + b_y))
				{
					game->py += round(MOVE_SPEED * sin(rad(game->view)));
					game->px += round(MOVE_SPEED * cos(rad(game->view)));
				}
			}
		}
	}
	return (0);
}

int	move_back(t_game *game)
{
	double	bx;
	double	by;

	bx = round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view)));
	by = round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view)));
	if (game->key[115])
	{
		if (!is_wall(game, game->px - bx, game->py - by))
		{
			game->py -= round(MOVE_SPEED * sin(rad(game->view)));
			game->px -= round(MOVE_SPEED * cos(rad(game->view)));
		}
	}
	return (0);
}

int	move_right(t_game *game)
{
	double	bx;
	double	by;

	bx = round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view)));
	by = round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view)));
	if (game->key[100] && !is_wall(game, game->px - bx, game->py + by))
	{
		game->px -= round(MOVE_SPEED * sin(rad(game->view)));
		game->py += round(MOVE_SPEED * cos(rad(game->view)));
	}
	return (0);
}

int	move_left(t_game *game)
{
	double	bx;
	double	by;

	bx = round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view)));
	by = round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view)));
	if (game->key[97] && !is_wall(game, game->px + bx, game->py - by))
	{
		game->px += round(MOVE_SPEED * sin(rad(game->view)));
		game->py -= round(MOVE_SPEED * cos(rad(game->view)));
	}
	return (0);
}

void	player_moves(t_game *game)
{
	if (game->key[130])
	{
		game->view += 2;
		if (game->view > 360)
			game->view = 0;
	}
	if (game->key[131])
	{
		game->view -= 2;
		if (game->view < 0)
			game->view = 360;
	}
	move_front(game);
	move_back(game);
	move_right(game);
	move_left(game);
}
