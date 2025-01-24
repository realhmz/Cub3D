#include "cub.h"

int	is_wall_p(t_game *game, double x, double y)
{
	int	i;
	int	j;

	i = (int)(x / 100);
	j = (int)(y / 100);
	if (x <= 0 || y <= 0)
		return (1);
	if (game->map[j] && game->map[j][i])
	{
		if (game->map[j][i] == '1')
		{
			return (1);
		}
	}
	return (0);
}

void	dda_vars_init2(t_dda *vars)
{
	if (vars->ray_dir_x < 0)
		vars->sidedist_x = (vars->pos_x - vars->map_x) * vars->deltadist_x;
	else
		vars->sidedist_x
			= (vars->map_x + 1.0 - vars->pos_x) * vars->deltadist_x;
	if (vars->ray_dir_y < 0)
		vars->sidedist_y = (vars->pos_y - vars->map_y) * vars->deltadist_y;
	else
		vars->sidedist_y
			= (vars->map_y + 1.0 - vars->pos_y) * vars->deltadist_y;
	vars->hit = 0;
	vars->i = 0;
}

void	dda_vars_init(t_game *game, double view, t_dda *vars)
{
	vars->ray_dir_x = cos(rad(view));
	vars->ray_dir_y = sin(rad(view));
	vars->pos_x = game->px / 100.0;
	vars->pos_y = game->py / 100.0;
	vars->map_x = (int)vars->pos_x;
	vars->map_y = (int)vars->pos_y;
	if (vars->ray_dir_x == 0)
		vars->deltadist_x = 1e30;
	else
		vars->deltadist_x = fabs(1 / vars->ray_dir_x);
	if (vars->ray_dir_y == 0)
		vars->deltadist_y = 1e30;
	else
		vars->deltadist_y = fabs(1 / vars->ray_dir_y);
	if (vars->ray_dir_x < 0)
		vars->step_x = -1;
	else
		vars->step_x = 1;
	if (vars->ray_dir_y < 0)
		vars->step_y = -1;
	else
		vars->step_y = 1;
	dda_vars_init2(vars);
}

double	end_point_while(t_game *game, t_dda *vars)
{
	double	min_wall_dist;

	min_wall_dist = 0.1;
	if (vars->sidedist_x < vars->sidedist_y)
	{
		vars->sidedist_x += vars->deltadist_x;
		vars->map_x += vars->step_x;
		vars->side = 0;
	}
	else
	{
		vars->sidedist_y += vars->deltadist_y;
		vars->map_y += vars->step_y;
		vars->side = 1;
	}
	if (vars->map_x < 0 || vars->map_y < 0
		|| vars->map_x >= game->map_width
		|| vars->map_y >= game->map_height)
		return (min_wall_dist * 100);
	return (0);
}
