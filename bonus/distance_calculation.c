#include "cub.h"

void	dda_vars_init2(t_dda *vars)
{
	if (vars->ray_dir_y < 0)
		vars->step_y = -1;
	else
		vars->step_y = 1;

	if (vars->ray_dir_x < 0)
		vars->sidedist_x = (vars->pos_x - vars->map_x) * vars->deltadist_x;
	else
		vars->sidedist_x = (vars->map_x + 1.0 - vars->pos_x) * vars->deltadist_x;
	if (vars->ray_dir_y < 0)
		vars->sidedist_y = (vars->pos_y - vars->map_y) * vars->deltadist_y;
	else
		vars->sidedist_y = (vars->map_y + 1.0 - vars->pos_y) * vars->deltadist_y;
	vars->hit = 0;
	vars->i = 0;
}
void	dda_vars_init(t_game *game, double view, t_dda *vars)
{
	vars->ray_dir_x = cos(rad(view));
	vars->ray_dir_y = sin(rad(view));
	vars->pos_x = game->Px / 100.0;
   	vars->pos_y = game->Py / 100.0;
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
	dda_vars_init2(vars);
}

void	dda_vars_init_mir(t_game *game, double view, t_dda *vars)
{
	vars->ray_dir_x = cos(rad(view));
	vars->ray_dir_y = sin(rad(view));
	vars->pos_x = game->miror_x / 100.0;
   	vars->pos_y = game->miror_y / 100.0;
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

	if (vars->ray_dir_x < 0)
		vars->sidedist_x = (vars->pos_x - vars->map_x) * vars->deltadist_x;
	else
		vars->sidedist_x = (vars->map_x + 1.0 - vars->pos_x) * vars->deltadist_x;
	if (vars->ray_dir_y < 0)
		vars->sidedist_y = (vars->pos_y - vars->map_y) * vars->deltadist_y;
	else
		vars->sidedist_y = (vars->map_y + 1.0 - vars->pos_y) * vars->deltadist_y;

	vars->hit = 0;
	vars->i = 0;
}
double	end_point_while(t_game *game, t_dda *vars)
{
	const double MIN_WALL_DIST = 0.1;
	 if (vars->sidedist_x <vars->sidedist_y)
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
		if (vars->map_x < 0 || vars->map_y < 0 || 
			vars->map_x >= game->map_width || 
			vars->map_y >= game->map_height)
			return MIN_WALL_DIST * 100;
	return (0);
}
double	end_point_while2(t_game *game, t_dda *vars)
{
	const double MIN_WALL_DIST = 0.1;
	if (game->map[vars->map_y][vars->map_x] == '1')
	{
		double dist;
		
		if (vars->side == 0)
			dist = vars->sidedist_x - vars->deltadist_x;
		else
			dist = vars->sidedist_y - vars->deltadist_y;
			
		if (dist < MIN_WALL_DIST)
			return MIN_WALL_DIST * 100;
		vars->hit = 1;
	}
	else if (game->map[vars->map_y][vars->map_x] == 'D')
	{
		double dist;

		game->side = 5;
		if (vars->side == 0)
			dist = vars->sidedist_x - vars->deltadist_x;
		else
			dist = vars->sidedist_y - vars->deltadist_y;
			
		if (dist < MIN_WALL_DIST)
			return MIN_WALL_DIST * 100;
		vars->hit = 1	;
	}
	return (0);
}
static double	get_wall_hit(t_game *game, double wall_x, int step, int side)
{
	if (side == 0)
	{
		if (step < 0)
		{
			if (game->side != 5)
				game->side = 1;
			return (100 - (int)((wall_x - floor(wall_x)) * 100));
		}
		else
		{
			if (game->side != 5)
				game->side = 2;
			return ((int)((wall_x - floor(wall_x)) * 100));
		}
	}
	else
	{
		if (step < 0)
		{
			if (game->side != 5)
				game->side = 3;
			return ((int)((wall_x - floor(wall_x)) * 100));
		}
		else
		{
			if (game->side != 5)
				game->side = 4;
			return (100 - (int)((wall_x - floor(wall_x)) * 100));
		}
	}
}

static double	calc_wall_dist(t_dda *vars, t_game *game, double *wall_x)
{
	double	wall_dist;

	if (vars->side == 0)
	{
		wall_dist = vars->sidedist_x - vars->deltadist_x;
		*wall_x = vars->pos_y + wall_dist * vars->ray_dir_y;
		game->hit_p = get_wall_hit(game, *wall_x, vars->step_x, 0);
	}
	else
	{
		wall_dist = vars->sidedist_y - vars->deltadist_y;
		*wall_x = vars->pos_x + wall_dist * vars->ray_dir_x;
		game->hit_p = get_wall_hit(game, *wall_x, vars->step_y, 1);
	}
	return (wall_dist);
}

double	end_point(t_game *game, double view)
{
	t_dda	vars;
	double	i;
	double	wall_x;
	double	wall_dist;

	dda_vars_init(game, view, &vars);
	game->side = 0;
	while (vars.hit == 0 && vars.i < 1000)
	{
		i = end_point_while(game, &vars);
		if (i)
			return (i);
		i = end_point_while2(game, &vars);
		if (i)
			return (i);
		vars.i++;
	}
	wall_dist = calc_wall_dist(&vars, game, &wall_x);
	return (wall_dist * 100);
}
