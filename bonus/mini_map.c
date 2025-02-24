#include  "cub.h"

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