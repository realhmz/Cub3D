#include "cub.h"

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
