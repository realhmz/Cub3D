/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:01:33 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/06 12:14:52 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flapy.h"

void    draw_bird(t_game *game)
{
    put_img_to_img(game->back, game->bird, game->bird_x, game->bird_y);
    mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0, 0);
}
void    render_map(t_game *game)
{
    int x;
    int y = 0;
    ft_put(game, game->sky, 0,0);
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == '1')
            {
                if (y == 0 || game->map[y - 1][x] == '0')
                    ft_put(game, game->up, x * 50, y * 50);
                else if (y == game->win_h / 50 -1 || game->map[y + 1][x] == '0')
                    ft_put(game, game->bot, x * 50, y * 50);
                else
                    ft_put(game, game->center, x * 50, y * 50);
                
            }
                if (y == game->win_h / 50 - 1)
                {
                    if (x % 2 == 0)
                        ft_put(game, game->floor1, x * 50, y * 50);
                    else
                        ft_put(game, game->floor2, x * 50, y * 50);
                }                
            x++;
        }
        y++;
    }
}

// void render_map(t_game *game)
// {
//     int x;
//     int y = 0;

//     ft_put(game, game->sky, 0, 0);  // Render sky
//     while (game->map[y])
//     {
//         x = 0;
//         while (game->map[y][x])
//         {
//             if (game->map[y][x] == '1')
//             {
//                 ft_put(game, game->wall, (x * 50) + game->wall_offset, y * 50);
//             }
//             x++;
//         }
//         y++;
//     }
// }

void    reset_map(t_game *game)
{
    int x = ft_strlen(game->map[1]) - 1;
    int y = 0;
    while (game->map[y])
    {
        game->map[y][x] = '0';
        y++;
    }
    
}
void    new_wall(t_game *game)
{
    int     i = rand();
    int     x;
    int     y = 0;
    static int  walls;
    char    **map;

    map = game->map;
    i %= 5;
    if (i == 0)
        i = 3;
    x = ft_strlen(map[0]) - 1;
    y = i;
    if (walls % 3 != 0)
    {
        walls++;
        return ;
    }
    i = 0;
    while (map[y] && y >= 0)
    {
        // if (y % 2 == 0)
        map[y][x] = '1';
        
        // else
            map[(game->win_h / 50)  - 1- y][x] = '1';
        y--;
    }
    walls++;
}
void    move_next(t_game *game)
{
    int x;
    int y;

    y = 0;
    x = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x] && x < ft_strlen(game->map[0]) - 1)
        {
            game->map[y][x] = game->map[y][x + 1];
            x++;
        }
        y++;        
    }
    
}


void    walls(t_game *game)
{
    static int i = 0;
    game->wall_offset -= 2;
    if (game->wall_offset <= 0)
    {
        i++;
        if (i == 15)
        {
            sleep(4);
        }
        
        game->wall_offset = 50;
        new_wall(game);
        move_next(game);
        reset_map(game);
    }
    
}
int render(t_game   *game)
{
    if (collition(game, game->bird_y, game->bird_x))
    {
        printf("Dead\n");
        exit(1);
    }
    apply_gravity(game);
    // move_walls(game);
    walls(game);
    render_map(game);
    draw_bird(game);
    limit_frame_rate(60);
    return (0);
}