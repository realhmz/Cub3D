#include "cub3d.h"

static void    bresenham_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) 
	{
        mlx_pixel_put(game->mlx, game->win, x0, y0, color);
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


void	draw_squar(t_game *game, int x, int y, int flag)
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
	else
	{
		while (y < j)
		{
			x = tmp;
			while (x < i)
			{
				if (y % 50 == 0 || x % 50 == 0)
					mlx_pixel_put(game->mlx, game->win, x, y, 0xFF0000);
				else
					mlx_pixel_put(game->mlx, game->win, x, y, 0xFFD700);
				x++;
			}
			y++;
		}
	}
}
void	load_map(t_game *game)
{
	int	x = 0;
	int	y = 0;
	while (game->map[y])
	{
		x  = 0;
		while (x < ft_strlen(game->map[y]))
		{
			if (game->map[y][x] == '1')
				draw_squar(game, x * 50, y * 50, 1);

			else
				draw_squar(game, x * 50, y * 50, 0);
			x++;
		}
		y++;
	}
}
void render_2d(t_game *game)
{
    int px = game->playerx;
    int py = game->playery;
    int i = px + 15;
    int j = py + 15;
    int tmp = px;

    while (py < j)
    {
        px = tmp;
        while (px < i)
        {
            mlx_pixel_put(game->mlx, game->win, px, py, 0xDE5140);
            px++;
        }
        py++;
    }
}

int key_press(int keycode, t_game *game)
{
    if (keycode < 256)
        game->key_states[keycode] = 1;
    return 0;
}

int key_release(int keycode, t_game *game)
{
    if (keycode < 256)
        game->key_states[keycode] = 0;
    return 0;
}

void update_player_position(t_game *game)
{
    if (game->key_states[119])
        game->playery -= 1;
    if (game->key_states[115])
        game->playery += 1;
    if (game->key_states[97])
        game->playerx -= 1;
    if (game->key_states[100])
        game->playerx += 1;
}

int move(t_game *game)
{

    update_player_position(game);
    load_map(game);
    render_2d(game);

    return 0;
}

void game_init(t_game *game)
{
    player_pos_real(game); 
    game->key_states = malloc(sizeof(int) * 256);
    memset(game->key_states, 0, sizeof(int) * 256); 
}

int main(int ac, char **av)
{
    t_game *game;

    if (ac != 2)
    {
        printf("Error\n");
        exit(127);
    }

    game = malloc(sizeof(t_game));
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, 800, 800, "Cub3d");

    read_map(game, av[1]);
    game_init(game);

    mlx_hook(game->win, 02, (1L << 0), key_press, game);
    mlx_hook(game->win, 03, (1L << 1), key_release, game);

    mlx_loop_hook(game->mlx, move, game);

    mlx_loop(game->mlx);

    return 0;
}