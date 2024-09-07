#include "cub3d.h"

void    bresenham_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) 
	{
        put_pixel_img(game->base, x0, y0, color);
        if (x0 == x1 && y0 == y1)
			break;
        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


void		draw_squar(t_game *game, int x, int y, int flag)
{
	int i = x + 50;
	int j = y + 50;
	int	tmp = x;
	int	tmp_y = y;
	
	x = tmp;
	y = tmp_y;

	if (flag == 1)
	{
		while (y < j)
		{
			x = tmp;
			while (x < i)
			{
				if (y % 50 == 0 || x % 50 == 0)
					mlx_pixel_put(game->mlx, game->win, x, y, 0xFF0000);
				else
					mlx_pixel_put(game->mlx, game->win, x, y, 0xFFFFFF);
				x++;
			}
			y++;
		}
	}
}
void *load_map_thread(void *arg)
{
    t_game *game = (t_game *)arg;

    while (1)
    {
        pthread_mutex_lock(&game->map_mutex);
        load_map(game); // Non-graphical operations can run here
        pthread_mutex_unlock(&game->map_mutex);

        // Introduce some sleep to avoid busy-waiting
        usleep(1000); // Sleep for 10ms
    }
    return NULL;
}

void	 load_map(t_game *game)
{
	int	x = 0;
	int	y = 0;
	while (game->map[y])
	{
		x  = 0;
		while (x < game->win_w / 50)
		{
            if (game->map[y][x] == 'P')
            {
                game->car_x = x;
                game->car_y = y;
                ft_put(game, game->car, x * 50, y * 50);
            }
            
			else if (game->map[y][x] == '1')
				ft_put(game, game->wall, x *50, y * 50);
			else if (game->map[y][x] == '0')
				put_edge(game, game->asset->e, x, y);
			
			// if (game->map[y][x] == '1')
			// 	draw_squar(game, x * 50, y * 50, 1);

			// else
			// 	draw_squar(game, x * 50, y * 50, 0);
			x++;
		}
		y++;
	}
    put_img_to_img(game->base, game->back, 0, 0);

}

void *load_rotate(void *arg)
{
    t_game *game = (t_game *)arg;

    while (1)
    {
        pthread_mutex_lock(&game->rotation_mutex);
	    rotate_car_image(game);

        // move(game); 
        pthread_mutex_unlock(&game->rotation_mutex);

        usleep(5000); // Sleep for 5ms to avoid busy-waiting
    }
    return NULL;
}
void *load_render(void *arg)
{
    t_game *game = (t_game *)arg;

    while (1)
    {
        pthread_mutex_lock(&game->rotation_mutex);
		render_2d(game);
        pthread_mutex_unlock(&game->rotation_mutex);
        usleep(5000); // Sleep for 5ms to avoid busy-waiting
    }
    return NULL;
}

void game_init(t_game *game)
{
    player_pos_real(game);
	game->asset = malloc(sizeof(t_asset));
	game->asset->e = malloc(sizeof(t_img) * 16);
    game->key_states = malloc(sizeof(int) * 256);
    memset(game->key_states, 0, sizeof(int) * 256);
	game->theta = 0;
    game->speed = 4;
    game->rotation_speed = 0.02;
	game->win_w = ft_strlen(game->map[0]) * 50;
	game->win_h = count_newline(game->map[0], game->map) * 50;
    player_pos(game);
	printf("%d    %d\n\n",game->win_h, game->win_w);
}
int print(t_game *game)
{
    int i = 0;
    while (game->map[i])
    {
        printf("%s\n",game->map[i]);
        i++;
    }
    // sleep (1);
    return (0);
}
// int main(int ac, char **av)
// {
//     t_game *game;

//     if (ac != 2)
//     {
//         printf("Error\n");
//         exit(127);
//     }
//     game = malloc(sizeof(t_game));
//     read_map(game, av[1]);
//     game_init(game);
//     game->mlx = mlx_init();
//     game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "Cub3d");
// 	game->base = new_img(game->win_w, game->win_h, game);
	
// 	edge_assets(game);
// 	// draw_squar(game,0,0,1);
// 	// pthread_mutex_init(&game->map_mutex, NULL);
// 	// pthread_mutex_init(&game->rotation_mutex, NULL);
// 	// pthread_create(&game->render_thread, NULL, &load_map_thread, (void *)game);
// 	// pthread_create(&game->rotation_thread, NULL, &load_rotate, (void *)game);
// 	// pthread_create(&game->rotation_thread, NULL, &load_render, (void *)game);
//     mlx_hook(game->win, 02, (1L << 0), key_press, game);
//     mlx_hook(game->win, 03, (1L << 1), key_release, game);
//     load_map(game);
//     mlx_loop_hook(game->mlx, move, game);
//     // mlx_loop_hook(game->mlx, print, game);

//     mlx_loop(game->mlx);

//     return 0;
// }

int main(int ac, char **av)
{
    t_game *game;

    if (ac != 2)
    {
        printf("Error\n");
        exit(127);
    }
    game = malloc(sizeof(t_game));
    read_map(game, av[1]);
    game_init(game);
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "Cub3d");
	game->base = new_img(game->win_w, game->win_h, game);
    game->back = new_img(game->win_w, game->win_h, game);
	game->car = new_file_img("car.xpm", game);
	game->wall = new_file_img("back.xpm", game);
    game->car_height = game->car.h;
    game->car_width = game->car.w;
    // Setup event hooks and loop hooks
    load_map(game);
    mlx_hook(game->win, 02, (1L << 0), key_press, game);
    mlx_hook(game->win, 03, (1L << 1), key_release, game);

    // Main game loop hook
    mlx_loop_hook(game->mlx, move, game);

    // Start the rendering loop
    mlx_loop(game->mlx);

    return 0;
}
