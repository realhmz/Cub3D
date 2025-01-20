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

t_img	get_door_img(t_game *game)
{
	if (game->distance < 80)
		return (game->door4);
	else if (game->distance > 80 && game->distance < 150)
		return (game->door3);
	else if (game->distance > 150 && game->distance < 200)
		return (game->door2);
	else
		return (game->door1);	
}
int get_wall_color(t_game *game, double curr_hit)
{
	int	color;
	if (game->p_flag)
	{
		// printf("hit p  %d ,, cur %d\n",game->p_hit_p, curr_hit);
		color =  get_pixel_img(game->player, game->p_hit_p,curr_hit);
		return color;
	}
	if (game->side == 1)
		return get_pixel_img(game->wall_w, game->hit_p, curr_hit);
	else if (game->side == 4)
		return get_pixel_img(game->wall_s, game->hit_p, curr_hit);
	else if (game->side == 2)
		return get_pixel_img(game->wall_e, game->hit_p, curr_hit);
	else if (game->side == 3)
		return get_pixel_img(game->wall_n, game->hit_p, curr_hit);
	else if (game->side == 7)
	{
		color = get_pixel_img(game->door1, game->hit_p, curr_hit);
		if (color)
		{
			return (color);
		}
		
	}
	else if (game->side == 6)
	{
		 return get_pixel_img(game->miror, game->hit_p, curr_hit);
	}
	return 0;
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
			put_pixel_img(game->back, x, (int)curr_y_up, color);
		}
		if (curr_y_down < 720 && curr_hit_down >= 0 && curr_hit_down <= 100)
		{
			int color = get_wall_color(game, curr_hit_down);
			color = calc_darkness(game, distance, color);
			put_pixel_img(game->back, x, (int)curr_y_down, color);
		}
		curr_y_up -= inc_y;
		curr_y_down += inc_y;
		curr_hit_up -= hit_y ;
		curr_hit_down += hit_y ;
		step--;
	}
	return 0;
}

int fix_draw_mir(int x, int y1, int y2, t_game *game, double distance)
{
	double step = 100 / 2;
	double inc_y = 1.0;
	double mid_y = 100 / 2 ;
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
			put_pixel_img(game->miror, x, (int)curr_y_up, color);
		}
		if (curr_y_down < 720 && curr_hit_down >= 0 && curr_hit_down <= 100)
		{
			int color = get_wall_color(game, curr_hit_down);
			color = calc_darkness(game, distance, color);
			put_pixel_img(game->miror, x, (int)curr_y_down, color);
		}
		curr_y_up -= inc_y;
		curr_y_down += inc_y;
		curr_hit_up -= hit_y ;
		curr_hit_down += hit_y ;
		step--;
	}
	return 0;
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
		put_pixel_img(game->back, (int)curr_x, (int)curr_y, color);
		curr_x += inc_x;
		curr_y += inc_y;
		i++;
	}
	return (500);
}

int	draw_line_simple_mir(int x1, int y1, int x2, int y2,t_game *game, int color)
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
		put_pixel_img(game->miror, (int)curr_x, (int)curr_y, color);
		curr_x += inc_x;
		curr_y += inc_y;
		i++;
	}
	return (500);
}

int	key_press(int keycode, t_game *game)
{
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
	int i;
	int j;

	i = x / 100;
	j = y / 100;
	if (x <= 0 || y <= 0)
		return (1);
	if (game->map[j] && game->map[j][i])
	{
		if (game->map[j][i] == '1' || game->map[j][i] =='M')
		{
			return (1);
		}
	}
	return (0);
}

int is_door(t_game *game, int x, int y)
{
	int i;
	int j;

	i = x / 100;
	j = y / 100;
	if (x <= 0 || y <= 0)
		return (1);
	if (game->map[j] && game->map[j][i])
	{
		if (game->map[j][i] == 'D')
		{
			return (1);
		}
	}
	return (0);
}
int is_wall_miror(t_game *game, int x, int y)
{
	int i;
	int j;

	i = x / 100;
	j = y / 100;
	if (x <= 0 || y <= 0)
		return (1);
	if (game->map[j] && game->map[j][i])
	{
		if (game->map[j][i] == '1' || game->map[j][i] == 'P')
		{
			return (1);
		}
	}
	return (0);
}


int	calc_darkness_2d(t_game *game, double dst, int color)
{
	int r = color / 256 / 256;
	int g = (color / 256) % 256;
	int b = color % 256;

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
	int r = color / 256 / 256;
	int g = (color / 256) % 256;
	int b = color % 256;

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

void ray_cast_mir(t_game *game)
{
	double view = 0;
	if (game->view > 90 && game->view < 260)
	{
		view = 0;
	}
	else
		view = 180;
	double min = view - 30; 
	double angle_step = 60.0 / 100;
	int color = 0xffd700;
	float ca = view - min;
	int ray = 0;
	int x;
	int line_height;
	int y_start;
	int y_end;
	double ray_angle;
	while (ray++ < 100)
	{
		ray_angle = min + ray * angle_step;
		game->miror_distance = end_point_miro(game, ray_angle);
		ca = view - ray_angle;
		if (ca < 0)
			ca = 360 + ca;
		if (ca > 360)
			ca = ca - 360;
		game->miror_distance = game->miror_distance * cos(rad(ca));
		x = ray * (100 / 100);
		line_height = (int)((100 * 100 ) / game->miror_distance);
		y_start = (100 / 2) - ((line_height ) / 2);
		y_end = (100 / 2) + ((line_height ) / 2);		
		game->hit_p_y = y_end - y_start;
		color = calc_darkness(game, game->miror_distance, color);
		if (color < 0 || color > 0xFFFFFF)
			continue;
		if (y_start < 0) y_start = 0;
		if (y_end < 1) y_end = 1;
		if (y_end >= 100) y_end = 100 - 1;		
		fix_draw_mir(x, y_start, y_end, game, game->miror_distance);
		if (game->side == 7)
		{
			put_img_to_img(game->back, game->door1, 500, 100);
		}

		draw_line_simple_mir(x, y_end, x, 100, game, calc_darkness(game, game->miror_distance, 0x0F282F));
		draw_line_simple_mir(x, y_start, x, 0, game, 0x19325F);
	}
}
void draw_ceiling(int x, int y_start, t_game *game, double ray_angle)
{
    double dir_x = cos(rad(ray_angle));
    double dir_y = sin(rad(ray_angle));
    int y;

    for (y = 0; y < y_start; y++)
    {
        // Calculate fixed texture coordinates based on screen position
        int tx = (x * 64 / 1280) % 64;  // Map screen x to texture x
        int ty = (y * 64 / 360) % 64;   // Map screen y to texture y
        
        if (tx < 0) tx += 64;
        if (ty < 0) ty += 64;
        
        // Get color from ceiling texture
        int color = get_pixel_img(game->ceiling_img, tx, ty);
        
        // Apply distance fog effect
        double current_dist = 720.0 / (2.0 * y - 720);
        color = calc_darkness(game, current_dist, color);
        
        put_pixel_img(game->back, x, y, color);
    }
}
void ray_cast(t_game *game)
{
	double view = game->view;
	double min = view - 30; 
	double angle_step = 60.0 / 1280;
	int color = 0xffd700;
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
		y_start = (720 / 2) - ((line_height ) / 2);
		y_end = (720 / 2) + ((line_height ) / 2);		
		game->hit_p_y = y_end - y_start;
		color = calc_darkness(game, game->distance, color);
		if (color < 0 || color > 0xFFFFFF)
			continue;
		if (y_start < 0) y_start = 0;
		if (y_end < 1) y_end = 1;
		if (y_end >= 720) y_end = 720 - 1;		
		fix_draw(x, y_start, y_end, game, game->distance);
		draw_line_simple(x, y_end, x, 720, game, calc_darkness(game, game->distance, game->floor_color));
		// draw ceiling 
		// draw_ceiling(x, y_start,game, ray_angle);
		draw_line_simple(x, y_start, x, 0, game, game->ceiling_color);
	}
}
int	move_front(t_game *game)
{
	if (game->key[119])
	{
		if (!is_wall(game, game->Px + round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view))), game->Py + round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view)))))
		{
			if (!is_wall(game, game->Px + round(MOVE_SPEED * cos(rad(game->view + 30))), game->Py + round(MOVE_SPEED * sin(rad(game->view + 30)))))
			{
				if (!is_wall(game, game->Px + round(MOVE_SPEED * cos(rad(game->view - 30))), game->Py + round(MOVE_SPEED * sin(rad(game->view - 30)))))
				{
					game->Py += round(MOVE_SPEED * sin(rad(game->view)));
					game->Px += round(MOVE_SPEED * cos(rad(game->view)));
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
		if (!is_wall(game, game->Px - round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view))), game->Py - round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view)))))
		{
			game->Py -= round(MOVE_SPEED * sin(rad(game->view)));
			game->Px -= round(MOVE_SPEED * cos(rad(game->view)));
			return (1);
		}
	}
	return (0);
}
int move_right(t_game *game)
{
	if (game->key[100] && !is_wall(game, game->Px - round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view))), game->Py + round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view)))))
	{
		game->Px -= round(MOVE_SPEED * sin(rad(game->view)));
		game->Py += round(MOVE_SPEED * cos(rad(game->view)));
		return (1);
	}
	return (0);
}
int	move_left(t_game *game)
{
	if (game->key[97] && !is_wall(game, game->Px + round((MOVE_SPEED + PLAYER_BUFFER) * sin(rad(game->view))), game->Py - round((MOVE_SPEED + PLAYER_BUFFER) * cos(rad(game->view)))))
	{
		game->Px += round(MOVE_SPEED * sin(rad(game->view)));
		game->Py -= round(MOVE_SPEED * cos(rad(game->view)));
		return (1);
	}
	return (0);
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
	move_front(game);
	move_back(game);
	move_right(game);
	move_left(game);
	
}
void    draw_square(t_game *game, int x, int y, int color)
{
	int dst_y = y + 25;
	int dst_x = x + 25;
	int save_x = x;
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
	// int	x;
	// int	y;
	int	save_x = 0, save_y = 0;
	double	x;
	double	y;
	x = game->Px / 4.0;
	y = game->Py / 4.0;
	// printf("px  %d , py  %d\n",x, y);
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
	int x = 0;
	int y = 0;
	y = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y] && game->map[y][x])
		{
			if (game->map[y][x] == '1')
			{
				draw_square(game, x * 25, y * 25, 0xB4B4B4);
			}
			else if (game->map[y][x] == 'M')
			{
				draw_square(game, x * 25, y * 25, 0x747474);	
			}
			else if (game->map[y][x] == 'D')
			{
				draw_square(game, x * 25, y * 25, 0xFFE199);
			}
			else if(game->map[y][x])
			{
				draw_square(game, x * 25, y * 25, 0x574b23);
			}
			x++;
		}
		y++;
	}
	fill_map_frame(game);
}
int	end_point_2d(t_game *game, int view)
{
	int	i = 0;
	int x = 0;
	int y = 0;
	while (i < 60)
	{
		x = game->Px / 4  + i * cos(rad(game->view));
		y = game->Py / 4 + i * sin(rad(game->view));
		// if (collide_with_wall_2d(game, x, y))
		if (is_wall(game, x * 100 / 25, y * 100 / 25))
			return (i);
		if (is_door(game, x * 100 / 25, y * 100 / 25))
		{
			if (i > 50)
			{
				if (view > game->view - 10 && view < game->view + 10) ;
				else
					return (i);
			}		
		}		
		i++;
	}
	return (i);
}
int	end_point_miror(t_game *game, int view)
{
	int	i = 0;
	int x = 0;
	int y = 0;
	while (i < 900)
	{
		x = game->miror_x / SCALE  + i * cos(rad(view));
		y = game->miror_y / SCALE + i * sin(rad(view));
		// if (collide_with_wall_2d(game, x, y))
		if (is_wall_miror(game, x * 100 / 25, y * 100 / 25))
		{
			return (i);
		}
		i++;
	}
	return (25);
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
		dst += 4;
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
	// put_pixel_img(game->back, x1, y1, color);
}
void	ray_cast_2d(t_game *game)
{
	int	view = game->view;
	int	min = view - 20;
	int color = 0x00ffff;
	int max = view + 20;
	while (min < max)
	{
		color = 0xffd700;
		int distance_x = end_point_2d(game, min) * cos(rad(min));
		int distance_y = end_point_2d(game, min) * cos(rad(min));
		int new_x = (game->Px) / SCALE  + end_point_2d(game, min) * cos(rad(min));
		int new_y = (game->Py)  / SCALE  + end_point_2d(game, min) * sin(rad(min));
		if (distance_x > distance_y)
			distance_y = distance_x;
		else
			distance_x = distance_y;
		// if (is_edge(game, end_point_2d(game, min), min))
		// {
		// 	draw_line_2d(game->Px / 100 * 25, game->Py / 100 * 25, new_x, new_y, game, 0x00ff00);
		// }
		if (game->hit_2d == 1)
			color = 0xffd700;
		if (game->hit_2d == 2)
			color = 0xffffff;
		game->hit_2d = 0;
		// else
		// {
			draw_line_2d((game->Px + 15) / SCALE, (game->Py + 15) / SCALE, new_x, new_y, game, color);
		// }
		// draw_line_2d(game->Px / SCALE, game->Py / SCALE, new_x, new_y, game, 0x00ff00);
		min ++;
	}
}
void	ray_cast_miror(t_game *game)
{
	int	view = 0;
	int	min = view - 15;
	int color = 0x00ffff;
	int max = view + 15;
	while (min < max)
	{
		color = 0x00ffff;
		int new_x = game->miror_x / SCALE  + end_point_miror(game, min) * cos(rad(min));
		int new_y = game->miror_y  / SCALE  + end_point_miror(game, min) * sin(rad(min));
		draw_line_2d(game->miror_x / SCALE, game->miror_y / SCALE, new_x, new_y, game, 0xffd700);
		min ++;
	}
	
}
void	miror(t_game *game)
{
	ray_cast_miror(game);
}
void	update_player(t_game *game)
{
	int px = game->Px / 100;
	int py = game->Py / 100;
	if (px < 0 || px > game->map_width || py < 0 || py > game->map_height)
		return;
	if (game->map[py] && game->map[py][px])
	{
		// printf("x %d, y %d\n",px,py);
		game->map[py][px] = 'P';

	}
	if (game->last_x != px || game->last_y  != py)
	{
		game->map[game->last_y][game->last_x] = '0';
		game->last_x = px;
		game->last_y = py;
	}
}
void *read_xpm_safely(void *mlx, int *width, int *height)
{
    int fd = open("../../Desktop/bonus/frame.xpm", O_RDONLY);
    if (fd == -1)
        return NULL;

    // Try to get shared lock (non-blocking)
    if (flock(fd, LOCK_SH | LOCK_NB) == -1) {
        close(fd);
        return NULL;
    }

    void *img = mlx_xpm_file_to_image(mlx, "../../Desktop/bonus/frame.xpm", width, height);
    
    // Release lock
    flock(fd, LOCK_UN);
    close(fd);

    return img;
}
void scale_camera_to_mirror(t_game *game)
{
    int src_w = 640;
    int src_h = 480;
    int dst_w = 100;
    int dst_h = 100;
    
    for (int y = 0; y < dst_h; y++)
    {
        for (int x = 0; x < dst_w; x++)
        {
            // Simple scaling calculation
            int src_x = x * src_w / dst_w;
            int src_y = y * src_h / dst_h;
            
            // Copy pixel directly
            int color = get_pixel_img(game->camera, src_x, src_y);
            put_pixel_img(game->camera_new, x, y, color);
        }
    }
}
int	move(t_game *game)
{
	player_moves(game);
	mlx_destroy_image(game->mlx, game->back.img_ptr);
	mlx_destroy_image(game->mlx, game->miror.img_ptr);
	// mlx_destroy_image(game->mlx, game->camera.img_ptr);
	mlx_destroy_image(game->mlx, game->mini_map.img_ptr);
	mlx_destroy_image(game->mlx, game->map_frame.img_ptr);
	// mlx_destroy_image(game->mlx, game->camera.img_ptr);
	game->back = new_img(1280, 720, game);
	game->miror = new_img(100, 100, game);
	game->map_frame = new_img(300, 300, game);
	game->mini_map = new_img(1280, 720, game);
	put_img_to_img(game->back, game->miror, 1000, 0);
	// game->camera = new_file_img_safe("frame.xpm", game);
	game->camera_new = new_img(100,100,game);
	// scale_camera_to_mirror(game);
	// ray_cast_mir(game);
	put_img_to_img(game->miror, game->miror_frame,0, 0);
	game->p_flag = 0;
	ray_cast(game);
	// miror(game);
	render(game);
	ray_cast_2d(game);
	render_player(game);
	put_img_to_img(game->map_frame, game->mini_map, (- game->Px / SCALE)  + 150, (- game->Py / SCALE) + 150);
	update_player(game);
	put_img_to_img(game->back, game->map_frame, 125, 385);
	put_img_to_img(game->back, game->gun,0,0);
	// print_map(game);
	// put_img_to_img(game->back, game->gun, 666, 450 );
	// put_img_to_img(game->back, game->cros, 615, 335);
	mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0, 0);
	// mlx_put_image_to_window(game->mlx, game->win, game->camera.img_ptr, 0, 0);
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
void	print_map(t_game *game)
{
	char **map;
	map = game->map;
	int y = 0;
	while (map && map[y])
	{
		printf("%s\n",map[y]);				
		y++;
	}
	
}
int	max_width(char **map)
{
	int	i;
	int	j;
	int max;

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

// void	*camera_loop(void *game)
// {

// }
int	get_ceiling_color(int *rgb)
{
	int res;

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
	{
		
		res = 0;
	}
	
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
	// game->view = get_pv(game->PV);
	// game->view = -90;
	game->camera = new_file_img_safe("frame.xpm", game);
	game->gun = new_file_img("gun_map.xpm", game);
	game->player = new_file_img("player1.xpm", game);
	game->cros = new_file_img("cros.xpm", game);
	game->miror_frame = new_file_img("miror1.xpm", game);
	game->ceiling_img = new_file_img("player1.xpm", game);
	game->wall_n = new_file_img(game->north, game);
	game->wall_s = new_file_img(game->south, game);
	game->wall_w = new_file_img(game->west, game);
	game->wall_e = new_file_img(game->east, game);
	game->door1 = new_file_img("door1.xpm", game);
}
int main(int ac, char **av)
{
	t_game  *game;
	// pthread_t *thread;
	// pthread_create(thread, NULL, camera_loop, NULL);
	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	if (!game)
		return (1);
	if (!parse_map(game))
	{
		return (ft_free(game), 1);
	}
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 1280, 720, "Cub3d");
	game_init(game);
	mlx_hook(game->win, 02, (1L << 0), key_press, game);
	mlx_hook(game->win, 03, (1L << 1), key_release, game);
	game->view = get_pv(game->PV);
	mlx_loop_hook(game->mlx, move, game);
	mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0, 0);
	mlx_loop(game->mlx);
	ft_free(game);
	return(0);
}
