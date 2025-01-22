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

int get_wall_color(t_game *game, double curr_hit)
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

int fix_draw(int x, t_game *game, double distance)
{
	double step = 720 / 2;
	double inc_y = 1.0;
	double mid_y = 720 / 2 ;
	double curr_y_up = mid_y;
	double curr_y_down = mid_y;
	double visible_height = game->hit_p_y;
	double hit_y = 100.0 / visible_height;
	double tex_start = 50.0;
	double curr_hit_up = tex_start;
	double curr_hit_down = tex_start;

	while (step > 0)
	{
		if (curr_y_up >= 0 && curr_hit_up >= 0 && curr_hit_up <= 100)
		{
			int color = get_wall_color(game, curr_hit_up);
			color = calc_darkness(distance, color);
			put_pixel_img(game->back, x, (int)curr_y_up, color);
		}
		if (curr_y_down < 720 && curr_hit_down >= 0 && curr_hit_down <= 100)
		{
			int color = get_wall_color(game, curr_hit_down);
			color = calc_darkness(distance, color);
			put_pixel_img(game->back, x, (int)curr_y_down, color);
		}
		curr_y_up -= inc_y;
		curr_y_down += inc_y;
		curr_hit_up -= hit_y ;
		curr_hit_down += hit_y ;
		step--;
	}
	return (0);
}

int	draw_line_simple(int x1, int y1, int x2, int y2,t_game *game, int color)
{
	double	step;
	double	dx;
	double	dy;
	double	inc_x;
	double	inc_y;
	double	curr_x;
	double	curr_y;
	int		i;

	dx = x2 - x1;
	dy = y2 - y1;
	if (abs((int)dx) > abs((int)dy))
		step = abs((int)dx);
	else
		step = abs((int)dy);
	inc_x = dx / step;
	inc_y = dy / step;
	curr_x = x1;
	curr_y = y1;
	i = 0;
	while (i <= step)
	{
		put_pixel_img(game->back, (int)curr_x, (int)curr_y,calc_darkness(i * 1.5, color));
		curr_x += inc_x;
		curr_y += inc_y;
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

int is_wall(t_game *game, int x, int y)
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
	int r;
	int g;
	int b;

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

void	ray_cast(t_game *game)
{
	double view = game->view;
	double min = view - 30; 
	double angle_step = 60.0 / 1280;
	float ca = view - min;
	int ray = 0;
	int line_height;
	int y_start;
	int y_end;
	double ray_angle;

	while (ray++ < 1280)
	{
		ray_angle = min + ray * angle_step;
		game->distance = end_point(game, ray_angle);
		ca = view - ray_angle;
		if (ca < 0)
			ca = 360 + ca;
		if (ca > 360)
			ca = ca - 360;
		game->distance = game->distance * cos(rad(ca));
		line_height = (int)((100 * 720 ) / game->distance);
		y_start = (720 / 2) - ((line_height ) / 2);
		y_end = (720 / 2) + ((line_height ) / 2);
		game->hit_p_y = y_end - y_start;
		fix_draw(ray, game, game->distance);
		draw_line_simple(ray, 720, ray, y_end, game, game->floor_color);
		draw_line_simple(ray, 0, ray, y_start, game, game->ceiling_color);
	}
}

int	move(t_game *game)
{
	player_moves(game);
	mlx_destroy_image(game->mlx, game->back.img_ptr);
	game->back = new_img(1280, 720, game);
	ray_cast(game);
	put_img_to_img(game->back, game->gun, 666, 450 );
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
