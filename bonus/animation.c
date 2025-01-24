#include "cub.h"

void	update_movement_shake(t_game *game)
{
	static double	shake_time;

	shake_time = 0.0;
	if (game->is_moving)
	{
		shake_time += SHAKE_FREQUENCY;
		game->movment_shake = sin(shake_time) * SHAKE_AMPLITUDE;
	}
	else
	{
		shake_time = 0.0;
		game->movment_shake *= 0.8;
		if (fabs(game->movment_shake) < 0.1)
			game->movment_shake = 0;
	}
}
