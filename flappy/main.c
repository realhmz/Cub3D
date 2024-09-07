/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:53:10 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/06 12:04:19 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flapy.h"

void    game_init(t_game *game)
{
    read_map(game, "map.bird");
    calc_win(game);
    game->wall_offset = 0;
    game->gravity_force = 0.5;
    player_pos_real(game);
    game->bird_y = 200;
    game->bird.velocity_y = 0;
    game->acceleration_y = 0.5;
    game->bird = new_file_img("bird.xpm", game);
    game->wall = new_file_img("wall.xpm", game);
    game->sky = new_file_img("back.xpm", game);
    
    game->up = new_file_img("./assets/up.xpm", game);
    game->center = new_file_img("./assets/center.xpm", game);
    game->bot = new_file_img("./assets/bot.xpm", game);
    game->floor1 = new_file_img("./assets/floor1.xpm", game);
    game->floor2 = new_file_img("./assets/floor1.xpm", game);
}


int main()
{
    t_game  *game;

    game = malloc(sizeof(t_game));
    game->mlx = mlx_init();
    game_init(game);
    game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "happy bird");
    game->back = new_img(game->win_w, game->win_h, game);
    
    mlx_key_hook(game->win, handle_key, game);
    render(game);
    sleep(2);
    mlx_loop_hook(game->mlx, render, game);
    // mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0, 0);
    // mlx_put_image_to_window(game->mlx, game->win, game->sky.img_ptr, 0, 0);
    mlx_loop(game->mlx);
}