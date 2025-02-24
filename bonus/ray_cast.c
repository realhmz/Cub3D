#include "cub.h"

double	rad(double angle)
{
	return (angle * M_PI / 180);
}

void	fix_init(t_game *game, t_fix *fix)
{
	fix->step = 720 / 2;
	fix->inc_y = 1.0;
	fix->mid_y = 720 / 2 ;
	fix->curr_y_up = fix->mid_y;
	fix->curr_y_down = fix->mid_y;
	fix->visible_height = game->hit_p_y;
	fix->hit_y = 100.0 / fix->visible_height;
	fix->tex_start = 50.0;
	fix->hit_up = fix->tex_start;
	fix->hit_down = fix->tex_start;
	fix->color = 0;
}

int	fix_draw(int x, t_game *game, double distance)
{
	t_fix	fix;

	fix_init(game, &fix);
	while (fix.step > 0)
	{
		if (fix.curr_y_up >= 0 && fix.hit_up >= 0 && fix.hit_up <= 100)
		{
			fix.color = get_wall_color(game, fix.hit_up);
			fix.color = calc_darkness(distance, fix.color);
			put_pixel_img(game->back, x, (int)fix.curr_y_up + game->movment_shake, fix.color);
		}
		if (fix.curr_y_down < 720 && fix.hit_down >= 0 && fix.hit_down <= 100)
		{
			fix.color = get_wall_color(game, fix.hit_down);
			fix.color = calc_darkness(distance, fix.color);
			put_pixel_img(game->back, x, (int)fix.curr_y_down + game->movment_shake, fix.color);
		}
		fix.curr_y_up -= fix.inc_y;
		fix.curr_y_down += fix.inc_y;
		fix.hit_up -= fix.hit_y ;
		fix.hit_down += fix.hit_y ;
		fix.step--;
	}
	return (0);
}

void	ray_init(t_game *game, t_ray *ray)
{
	ray->view = game->view;
	ray->min = ray->view - 30;
	ray->angle_step = 60.0 / 1280;
	ray->ca = ray->view - ray->min;
	ray->ray = 0;
	ray->line_height = 0;
	ray->y_start = 0;
	ray->y_end = 0;
	ray->ray_angle = 0;
}

void	ray_cast(t_game *game)
{
	t_ray	ray;

	ray_init(game, &ray);
	while (ray.ray++ < 1280)
	{
		ray.ray_angle = ray.min + ray.ray * ray.angle_step;
		game->distance = end_point(game, ray.ray_angle);
		ray.ca = ray.view - ray.ray_angle;
		if (ray.ca < 0)
			ray.ca = 360 + ray.ca;
		if (ray.ca > 360)
			ray.ca = ray.ca - 360;
		game->distance = game->distance * cos(rad(ray.ca));
		ray.line_height = (int)(100 * 720 / game->distance);
		ray.y_start = (720 / 2) - (ray.line_height / 2);
		ray.y_end = (720 / 2) + (ray.line_height / 2);
		game->hit_p_y = ray.y_end - ray.y_start;
		fix_draw(ray.ray, game, game->distance);
		game->color = game->floor_color;
		draw_line_simple(ray.ray, 720, ray.y_end, game);
		game->color = game->ceiling_color;
		draw_line_simple(ray.ray, 0, ray.y_start, game);
	}
}
