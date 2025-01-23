#include "cub.h"

double	rad(double angle)
{
	return (angle * M_PI / 180);
}

void	ft_free(t_game *game)
{
	int	i;

	free(game->save);
	free(game->ceiling);
	free(game->floor);
	if (game->east)
		free(game->east);
	if (game->south)
		free(game->south);
	if (game->north)
		free(game->north);
	if (game->west)
		free(game->west);
	i = -1;
	if (game->map)
	{
		if (game->map[++i])
			while (game->map && game->map[i])
				free(game->map[i++]);
		free(game->map);
	}
	free(game);
}

int	get_wall_color(t_game *game, double curr_hit)
{
	if (game->side == 1)
		return (get_pixel_img(game->wall_w, game->hit_p, curr_hit));
	else if (game->side == 4)
		return (get_pixel_img(game->wall_s, game->hit_p, curr_hit));
	else if (game->side == 2)
		return (get_pixel_img(game->wall_e, game->hit_p, curr_hit));
	else if (game->side == 3)
		return (get_pixel_img(game->wall_n, game->hit_p, curr_hit));
	return (0);
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
			put_pixel_img(game->back, x, (int)fix.curr_y_up, fix.color);
		}
		if (fix.curr_y_down < 720 && fix.hit_down >= 0 && fix.hit_down <= 100)
		{
			fix.color = get_wall_color(game, fix.hit_down);
			fix.color = calc_darkness(distance, fix.color);
			put_pixel_img(game->back, x, (int)fix.curr_y_down, fix.color);
		}
		fix.curr_y_up -= fix.inc_y;
		fix.curr_y_down += fix.inc_y;
		fix.hit_up -= fix.hit_y ;
		fix.hit_down += fix.hit_y ;
		fix.step--;
	}
	return (0);
}

void	line_init(t_line *line, int x1, int y1, int y2)
{
	line->dx = x1 - x1;
	line->dy = y2 - y1;
	if (abs((int)line->dx) > abs((int)line->dy))
		line->step = abs((int)line->dx);
	else
		line->step = abs((int)line->dy);
	line->inc_x = line->dx / line->step;
	line->inc_y = line->dy / line->step;
	line->curr_x = x1;
	line->curr_y = y1;
}

int	draw_line_simple(int x1, int y1, int y2, t_game *game)
{
	t_line	line;
	int		i;
	int		color;

	line_init(&line, x1, y1, y2);
	i = 0;
	while (i <= line.step)
	{
		color = calc_darkness(i * 1.5, game->color);
		put_pixel_img(game->back, (int)line.curr_x, (int)line.curr_y, color);
		line.curr_x += line.inc_x;
		line.curr_y += line.inc_y;
		i++;
	}
	return (500);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(win(game));
	if (keycode == 65363)
		game->key[130] = 1;
	if (keycode == 65361)
		game->key[131] = 1;
	if (keycode <= 127)
		game->key[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 65363)
		game->key[130] = 0;
	if (keycode == 65361)
		game->key[131] = 0;
	if (keycode <= 127)
		game->key[keycode] = 0;
	return (0);
}

int	is_wall(t_game *game, int x, int y)
{
	int	i;
	int	j;

	i = x / 100;
	j = y / 100;
	if (x <= 0 || y <= 0)
		return (1);
	if (game->map[j] && game->map[j][i])
	{
		if (game->map[j][i] == '1')
			return (1);
	}
	return (0);
}

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

int	move(t_game *game)
{
	player_moves(game);
	mlx_destroy_image(game->mlx, game->back.img_ptr);
	game->back = new_img(1280, 720, game);
	ray_cast(game);
	put_img_to_img(game->back, game->gun, 666, 450);
	mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0, 0);
	return (0);
}

void	game_init(t_game *game)
{
	game->back = new_img(1280, 720, game);
	game->key = malloc(sizeof(char) * 150);
	game->view = 0;
	game->ceiling_color = get_ceiling_color(game->ceiling);
	game->floor_color = get_ceiling_color(game->floor);
	game->map_height = calc_map_h(game->map);
	game->map_width = max_width(game->map);
	game->key = memset(game->key, 0, 150);
	game->gun = new_file_img("gun.xpm", game);
	game->wall_n = new_file_img(game->north, game);
	game->wall_s = new_file_img(game->south, game);
	game->wall_w = new_file_img(game->west, game);
	game->wall_e = new_file_img(game->east, game);
	game->view = get_pv(game->pv);
}

int	win(t_game *game)
{
	free(game->key);
	mlx_destroy_image(game->mlx, game->wall_e.img_ptr);
	mlx_destroy_image(game->mlx, game->wall_s.img_ptr);
	mlx_destroy_image(game->mlx, game->wall_w.img_ptr);
	mlx_destroy_image(game->mlx, game->wall_n.img_ptr);
	mlx_destroy_image(game->mlx, game->gun.img_ptr);
	mlx_destroy_image(game->mlx, game->back.img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	ft_free(game);
	exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	if (!game)
		return (1);
	if (!parse_map(game))
		return (ft_free(game), 1);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1280, 720, "Cub3d");
	game_init(game);
	mlx_hook(game->win, 17, 0, win, game);
	mlx_hook(game->win, 02, (1L << 0), key_press, game);
	mlx_hook(game->win, 03, (1L << 1), key_release, game);
	mlx_loop_hook(game->mlx, move, game);
	mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0, 0);
	mlx_loop(game->mlx);
	ft_free(game);
	return (0);
}
