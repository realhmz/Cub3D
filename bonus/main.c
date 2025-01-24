#include "cub.h"

double	rad(double angle)
{
	return (angle * M_PI / 180);
}

void    ft_free(t_game *game)
{
	int i;

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
	else if (game->side == 5)
		return (get_pixel_img(game->door1, game->hit_p, curr_hit));
	return (0);
}

int fix_draw(int x, int y1, int y2, t_game *game, double distance)
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
			color = calc_darkness(game, distance, color);
			put_pixel_img(game->back, x, (int)curr_y_up + game->movment_shake, color);
		}
		if (curr_y_down < 720 && curr_hit_down >= 0 && curr_hit_down <= 100)
		{
			int color = get_wall_color(game, curr_hit_down);
			color = calc_darkness(game, distance, color);
			put_pixel_img(game->back, x, (int)curr_y_down + game->movment_shake, color);
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
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	inc_x = dx / step;
	inc_y = dy / step;
	curr_x = x1;
	curr_y = y1;
	i = 0;
	while (i <= step)
	{
		put_pixel_img(game->back, (int)curr_x, (int)curr_y, calc_darkness(game, i * 1.5, color));
		curr_x += inc_x;
		curr_y += inc_y;
		i++;
	}
	return (500);
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
		if (game->map[j][i] == '1' || game->map[j][i] == 'D')
			return (1);
	}
	return (0);
}

int is_door(t_game *game, int x, int y)
{
	int	i;
	int	j;

	i = x / 100;
	j = y / 100;
	if (x <= 0 || y <= 0)
		return (1);
	if (game->map[j] && game->map[j][i])
	{
		if (game->map[j][i] == 'D')
			return (1);
	}
	return (0);
}

int	calc_darkness_2d(t_game *game, double dst, int color)
{
	int r;
	int g;
	int b;

	r = color / 256 / 256;
	g = (color / 256) % 256;
	b = color % 256;
	r = r - (dst / 2);
	g = g - (dst / 2);
	b = g - (dst / 2);
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

int	calc_darkness(t_game *game, double dst, int color)
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
	int x;
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
		x = ray * (1280 / 1280);
		line_height = (int)((100 * 720 ) / game->distance);
		y_start = (720 / 2) - ((line_height ) / 2) + game->movment_shake;
		y_end = (720 / 2) + ((line_height ) / 2) + game->movment_shake;		
		game->hit_p_y = y_end - y_start;
		if (y_start < 0) y_start = 0;
		if (y_end < 1) y_end = 1;
		if (y_end >= 720) y_end = 720 - 1;		
		fix_draw(x, y_start, y_end, game, game->distance);
		draw_line_simple(x, 720, x, y_end, game, game->floor_color);
		draw_line_simple(x, 0, x, y_start, game, game->ceiling_color);
	}
}

int	move_front(t_game *game)
{
	if (game->key[119])
	{
		if (!is_wall(game, game->px + round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view))), game->py + round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view)))))
		{
			if (!is_wall(game, game->px + round(MOVE_SPEED * cos(rad(game->view + 30))), game->py + round(MOVE_SPEED * sin(rad(game->view + 30)))))
			{
				if (!is_wall(game, game->px + round(MOVE_SPEED * cos(rad(game->view - 30))), game->py + round(MOVE_SPEED * sin(rad(game->view - 30)))))
				{
					game->py += round(MOVE_SPEED * sin(rad(game->view)));
					game->px += round(MOVE_SPEED * cos(rad(game->view)));
					game->is_moving = 1;

					return (1);
				}
			}
		}
	}
	return (0);
}

int	move_back(t_game *game)
{
	if (game->key[115])
	{
		if (!is_wall(game, game->px - round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view))), game->py - round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view)))))
		{
			game->py -= round(MOVE_SPEED * sin(rad(game->view)));
			game->px -= round(MOVE_SPEED * cos(rad(game->view)));
			game->is_moving = 1;
			return (1);
		}
	}
	return (0);
}

int	move_right(t_game *game)
{
	if (game->key[100] && !is_wall(game, game->px - round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view))), game->py + round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view)))))
	{
		game->is_moving = 1;
		game->px -= round(MOVE_SPEED * sin(rad(game->view)));
		game->py += round(MOVE_SPEED * cos(rad(game->view)));
		return (1);
	}
	return (0);
}

int	move_left(t_game *game)
{
	if (game->key[97] && !is_wall(game, game->px + round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view))), game->py - round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view)))))
	{
		game->is_moving = 1;
		game->px += round(MOVE_SPEED * sin(rad(game->view)));
		game->py -= round(MOVE_SPEED * cos(rad(game->view)));
		return (1);
	}
	return (0);
}

void	open_door(t_game *game)
{
	int	dst;
	int	x;
	int	y;

	dst = end_point_door(game, game->view);
	if (dst)
	{
		x = game->px / 4  + dst * cos(rad(game->view));
		y = game->py / 4 + dst * sin(rad(game->view));
		if (is_door(game, x * 100 / 25, y * 100 / 25))
			game->map[y / 25][x / 25] = 'O';
	}
}

void	player_moves(t_game *game)
{
	if (game->key[130])
	{
		game->view += 5;
		if (game->view > 360)
			game->view = 0;
	}
	if (game->key[131])
	{
		game->view -= 5;
		if (game->view < 0)
			game->view = 360;
	}
	if (game->key['e'])
		open_door(game);
	move_front(game);
	move_back(game);
	move_right(game);
	move_left(game);
	if (!game->key[97] && !game->key[119] && !game->key[115] && !game->key[100])
		game->is_moving = 0;
	if (game->is_moving)
		update_movement_shake(game);
	else
		game->movment_shake = 0;
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int dst_y;
	int dst_x;
	int save_x;

	dst_y = y + 25;
	dst_x = x + 25;
	save_x = x;
	while (y <=  dst_y)
	{
		x = save_x;
		while (x <= dst_x)
		{
			put_pixel_img(game->mini_map, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_player(t_game *game)
{
	int	save_x = 0, save_y = 0;
	double	x;
	double	y;

	x = game->px / 4.0;
	y = game->py / 4.0;
	x += 0;
	y += 0;
	save_x = x;
	save_y = y;
	while (x <= save_x + 10)
	{
		y = save_y;
		while (y <= save_y + 10)
		{
			put_pixel_img(game->mini_map, x, y, 0xffd700);
			y++;
		}
		x++;
	}
}

void	fill_map_frame(t_game *game)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	while (x < 300)
	{
		y = 0;
		while (y < 300)
		{
			put_pixel_img(game->map_frame, x, y, 0x453321);
			y++;
		}
		x++;
	}
}

void    render(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y] && game->map[y][x])
		{
			if (game->map[y][x] == '1')
				put_img_to_img(game->mini_map, game->wall_n, x * 25, y * 25);
			else if (game->map[y][x] == 'M')
				draw_square(game, x * 25, y * 25, 0x747474);
			else if (game->map[y][x] == 'D')
				put_img_to_img(game->mini_map, game->door1, x * 25, y * 25);
			else if(game->map[y][x])
				draw_square(game, x * 25, y * 25, 0x000001);
			x++;
		}
		y++;
	}
	fill_map_frame(game);
}

int	end_point_2d(t_game *game, int view)
{
	int	i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (i < 60)
	{
		x = game->px / 4  + i * cos(rad(view));
		y = game->py / 4 + i * sin(rad(view));
		if (is_wall(game, x * 100 / 25, y * 100 / 25))
			return (i);
		i++;
	}
	return (i);
}

int	end_point_door(t_game *game, int view)
{
	int	i;
	int x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (i < 20)
	{
		x = game->px / 4  + i * cos(rad(view));
		y = game->py / 4 + i * sin(rad(view));
		if (is_door(game, x * 100 / 25, y * 100 / 25))
			return (i);
		i++;
	}
	return (0);
}

void	draw_line_2d(int x0, int y0, int x1, int y1, t_game *game, int color)
{
	int	x;
	int	y;
	int	step_x;
	int	step_y;
	int	err;
	int	e2;
	int	dst;

	x = x0;
	y = y0;
	dst = 80;
	step_x = (x1 > x0) - (x1 <= x0);
	step_y = (y1 > y0) - (y1 <= y0);
	err = abs(x1 - x0) - abs(y1 - y0);
	while (x != x1 || y != y1)
	{
		dst += 10;
		put_pixel_img(game->mini_map, x, y, calc_darkness_2d(game, dst, color));
		e2 = 2 * err;
		if (e2 > - abs(y1 - y0))
		{
			err = err - abs(y1 - y0);
			x = x + step_x;
		}
		if (e2 < abs(x1 - x0))
		{
			err = err + abs(x1 - x0);
			y = y + step_y;
		}
	}
}

void	ray_cast_2d(t_game *game)
{
	int	min;
	int color;
	int max;
	int new_x;
	int new_y;

	min = game->view - 25;
	color = 0xFFD700;
	max = game->view + 25;
	while (min < max)
	{
		new_x = (game->px) / SCALE  + end_point_2d(game, min) * cos(rad(min));
		new_y = (game->py) / SCALE  + end_point_2d(game, min) * sin(rad(min));
		min++;
		draw_line_2d((game->px + 15) / SCALE, (game->py + 15)
			/ SCALE, new_x, new_y, game, color);
	}
}

void	update_player(t_game *game)
{
	int px;
	int py;
	static	int	is_door;
	static	int	next_door;

	px = game->px / 100;
	py = game->py / 100;
	if (px < 0 || px > game->map_width || py < 0 || py > game->map_height)
		return;
	if (game->map[py] && game->map[py][px])
	{
		if (game->map[py][px] == 'D' || game->map[py][px] == 'O')
			is_door = 1;
		else
			is_door = 0;
		game->map[py][px] = 'P';

	}
	if (game->last_x != px || game->last_y  != py)
	{
		if (next_door)
			game->map[game->last_y][game->last_x] = 'D';
		else
			game->map[game->last_y][game->last_x] = '0';
		if (is_door)
			next_door = 1;
		else
			next_door = 0;
		
		game->last_x = px;
		game->last_y = py;
	}
}

int	move(t_game *game)
{
	player_moves(game);
	mlx_destroy_image(game->mlx, game->back.img_ptr);
	mlx_destroy_image(game->mlx, game->mini_map.img_ptr);
	mlx_destroy_image(game->mlx, game->map_frame.img_ptr);
	game->back = new_img(1280, 720, game);
	game->map_frame = new_img(300, 300, game);
	game->mini_map = new_img(1280, 720, game);
	game->p_flag = 0;
	ray_cast(game);
	render(game);
	ray_cast_2d(game);
	render_player(game);
	put_img_to_img(game->map_frame, game->mini_map, (- game->px / SCALE)  + 150, (- game->py / SCALE) + 150);
	update_player(game);
	put_img_to_img(game->back, game->map_frame, 125, 395 + game->movment_shake / 2);
	put_img_to_img(game->back, game->gun,0,15 + game->movment_shake / 2);
	mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0, 0);
	return (0);
}

int	calc_map_h(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	max_width(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = ft_strlen(map[0]);
	while (map && map[i])
	{
		j = ft_strlen(map[i]);
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

int	get_ceiling_color(int *rgb)
{
	int	res;

	res = rgb[0] * 256 * 256;
	res += rgb[1] * 256;
	res += rgb[2];
	return (res);
}

int	get_pv(char pv)
{
	int	res;

	if (pv == 'N')
		res = 270;
	else if (pv == 'S')
		res = 90;
	else if (pv == 'W')
		res = 180;
	else if (pv == 'E')
		res = 0;
	return (res);
}

void	game_init(t_game *game)
{
	game->ceiling_color = get_ceiling_color(game->ceiling);
	game->floor_color = get_ceiling_color(game->floor);
	game->back = new_img(1280, 720, game);
	game->miror = new_img(100, 100, game);
	game->mini_map = new_img(1280, 720, game);
	game->map_frame = new_img(150, 150, game);
	game->key = malloc(sizeof(char) * 150);
	game->map_height = calc_map_h(game->map);
	game->map_width = max_width(game->map);
	game->key = memset(game->key, 0, 150);
	game->gun = new_file_img("gun_map.xpm", game);
	game->wall_n = new_file_img(game->north, game);
	game->wall_s = new_file_img(game->south, game);
	game->wall_w = new_file_img(game->west, game);
	game->wall_e = new_file_img(game->east, game);
	game->door1 = new_file_img("door1.xpm", game);
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
	game->view = get_pv(game->pv);
	mlx_loop_hook(game->mlx, move, game);
	mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0, 0);
	mlx_loop(game->mlx);
	ft_free(game);
	return (0);
}
