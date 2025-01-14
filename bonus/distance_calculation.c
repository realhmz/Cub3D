#include "cub.h"

int is_wall_p(t_game *game, double x, double y)
{
	int i;
	int j;

	// i = (int)floor(x / 100);
	// j = (int)floor(y / 100);
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
int is_wall_m(t_game *game, double x, double y)
{
	int i;
	int j;

	// i = (int)floor(x / 100);
	// j = (int)floor(y / 100);
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
		if (game->map[j][i] == 'P')
		{
			return (2);
		}
		
	}
	return (0);
}
int is_wall_P(t_game *game, double x, double y)
{
	int i;
	int j;

	// i = (int)floor(x / 100);
	// j = (int)floor(y / 100);
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
		if (game->map[j][i] == 'M')
		{
			return (2);
		}
		
	}
	return (0);
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
		{
			game->side = 3;
			return ((int)((wall_x - floor(wall_x)) * 100));
		}
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

double	end_point_ppp(t_game *game, double view)
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

double end_point(t_game *game, double view)
{
    const double cos_view = cos(rad(view));
    const double sin_view = sin(rad(view));
    const int map_width = game->map_width * 100;
    const int map_height = game->map_height * 100;
    double ray_x = game->Px;
    double ray_y = game->Py;
    const double dx = cos_view * 1.0;
    const double dy = sin_view * 1.0;
    const int max_steps = (map_width + map_height) / 1;
    int steps = 0;
	const double EPSILON = 0.9999;
	double delta_x;
	double delta_y;
	double x_decimal;
	double y_decimal;

    while (steps < max_steps)
    {
        ray_x += dx;
        ray_y += dy;
        if (ray_x < 0 || ray_y < 0 || ray_x >= map_width || ray_y >= map_height)
            break;
		if (is_wall_P(game, (int)ray_x, (int)ray_y))
        {
			
            delta_x = ray_x - game->Px;
            delta_y = ray_y - game->Py;
			x_decimal = fmod(ray_x, 100);
			y_decimal = fmod(ray_y, 100);
			if (is_wall_P(game, (int)ray_x, (int)ray_y) == 2)
			{
				game->side = 6;
				game->hit_p = (int)y_decimal;
			}
			else if (x_decimal < 2 * EPSILON)
			{
				game->side = 1;  // West wall
				game->hit_p = (int)y_decimal;
			}
			else if (y_decimal > (100 - 2 * EPSILON))
			{
				game->side = 4;  // South wall
				game->hit_p = (int)x_decimal;
			}
			else if (x_decimal > (100 - 2 * EPSILON))
			{
				game->side = 2;  // East wall
				game->hit_p = (int)(100 - y_decimal);
			}
			else if (y_decimal < 2 * EPSILON)
			{
				game->side = 3;  // North wall
				game->hit_p = (int)(100 - x_decimal);
			}
            return sqrt(delta_x * delta_x + delta_y * delta_y);
        }
        steps++;
    }
    delta_x = ray_x - game->Px;
    delta_y = ray_y - game->Py;
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

double end_point_miro(t_game *game, double view)
{
    const double cos_view = cos(rad(view));
    const double sin_view = sin(rad(view));
    const int map_width = game->map_width * 100;
    const int map_height = game->map_height * 100;
    double ray_x = game->miror_x;
    double ray_y = game->miror_y;
    const double dx = cos_view * 1.0;
    const double dy = sin_view * 1.0;
    const int max_steps = (map_width + map_height) / 1;
    int steps = 0;
	const double EPSILON = 0.9999;
	double delta_x;
	double delta_y;
	double x_decimal;
	double y_decimal;

    while (steps < max_steps)
    {
        ray_x += dx;
        ray_y += dy;
        if (ray_x < 0 || ray_y < 0 || ray_x >= map_width || ray_y >= map_height)
            break;
		game->p_flag = 0;
		if (is_wall_m(game, (int)ray_x, (int)ray_y))
        {
			
            delta_x = ray_x - game->miror_x;
            delta_y = ray_y - game->miror_y;
			x_decimal = fmod(ray_x, 100);
			y_decimal = fmod(ray_y, 100);
			if (is_wall_m(game, (int)ray_x, (int)ray_y) == 2)
			{
				// game->side = 5;
				game->p_flag = 1;
				game->p_hit_p = (int)y_decimal; 
				// game->hit_p = (int)y_decimal;
			}
			else if (x_decimal < 2 * EPSILON)
			{
				game->side = 1;  // West wall
				game->hit_p = (int)y_decimal;
			}
			else if (y_decimal > (100 - 2 * EPSILON))
			{
				game->side = 4;  // South wall
				game->hit_p = (int)x_decimal;
			}
			else if (x_decimal > (100 - 2 * EPSILON))
			{
				game->side = 2;  // East wall
				game->hit_p = (int)(100 - y_decimal);
			}
			else if (y_decimal < 2 * EPSILON)
			{
				game->side = 3;  // North wall
				game->hit_p = (int)(100 - x_decimal);
			}
            return sqrt(delta_x * delta_x + delta_y * delta_y);
        }
        steps++;
    }
    delta_x = ray_x - game->Px;
    delta_y = ray_y - game->Py;
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}