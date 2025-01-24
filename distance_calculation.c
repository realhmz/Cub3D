#include "cub.h"

int	calc_darkness(double dst, int color)
{
	int	r;
	int	g;
	int	b;

	r = color / 256 / 256;
	g = (color / 256) % 256;
	b = color % 256;
	r = r - (dst / 4);
	g = g - (dst / 4);
	b = b - (dst / 4);
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r * 256 * 256 + g * 256 + b);
}

double	end_point_while2(t_game *game, t_dda *vars)
{
	double	min_wall_dist;
	double	dist;

	min_wall_dist = 0.1;
	if (game->map[vars->map_y][vars->map_x] == '1')
	{
		if (vars->side == 0)
			dist = vars->sidedist_x - vars->deltadist_x;
		else
			dist = vars->sidedist_y - vars->deltadist_y;
		if (dist < min_wall_dist)
			return (min_wall_dist * 100);
		vars->hit = 1;
	}
	return (0);
}

static double	get_wall_hit(t_game *game, double wall_x, int step, int side)
{
	if (side == 0)
	{
		if (step < 0)
		{
			game->side = 1;
			return (100 - (int)((wall_x - floor(wall_x)) * 100));
		}
		else
		{
			game->side = 2;
			return ((int)((wall_x - floor(wall_x)) * 100));
		}
	}
	else
	{
		if (step < 0)
			return (game->side = 3, ((int)((wall_x - floor(wall_x)) * 100)));
		else
		{
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
