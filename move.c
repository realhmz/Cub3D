/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:08:45 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/05 10:52:22 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void clear_img(t_img *img, int width, int height, int color)
{
    int x, y;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            put_pixel_img(*img, x, y, color);
        }
    }
}

void rotate_car_image(t_game *game)
{
    // if (game->needs_rotation)
    // {
        // Only rotate the car when a new rotation is requested
        // clear_img(&game->base, game->car.w + game->playerx, game->car.h+ game->playery, 0x000000); // Clear before redrawing
        
        // put_nimg_to_img(game->base, game->back, 0, 0, game->car.w + game->playerx, game->car.h+ game->playery);
        put_nimg_to_img(game->base, game->back, 0, 0, game->car.w + game->playerx, game->car.h+ game->playery);
        int img_width = game->car.w;
        int img_height = game->car.h;

        // Get the center of the image
        int cx = img_width / 2;
        int cy = img_height / 2;

        // Precompute the rotation once
        for (int y = 0; y < img_height; y++)
        {
            for (int x = 0; x < img_width; x++)
            {
                // Calculate relative position to center
                int rel_x = x - cx;
                int rel_y = y - cy;

                // Rotate the pixel around the center
                int new_x = (int)(cos(game->theta) * rel_x - sin(game->theta) * rel_y + cx);
                int new_y = (int)(sin(game->theta) * rel_x + cos(game->theta) * rel_y + cy);

                // Ensure the new position is within bounds
                if (new_x >= 0 && new_x < img_width && new_y >= 0 && new_y < img_height)
                {
                    // Get pixel color from original image
                    int color = get_pixel_img(game->car, x, y);

                    // Draw pixel at the rotated position
                    put_pixel_img(game->base, game->playerx + new_x, game->playery + new_y, color);
                }
            }
        }
    //     game->needs_rotation = 0; // Reset rotation flag
    // }

    // Draw the precomputed image to the screen
    mlx_put_image_to_window(game->mlx, game->win, game->base.img_ptr, 0, 0);
}

void render_2d(t_game *game)
{
    int px = game->playerx;
    int py = game->playery;
    int i = px + 15;
    int j = py + 15;
    int tmp = px;

	// clear_img(&game->base, game->playerx,game->playerx, 1);
	count_fps(game);
    // put_img_to_img(game->base, game->back, 0, 0);
    // mlx_put_image_to_window(game->mlx, game->win, game->back.img_ptr, 0,0);
	mlx_put_image_to_window(game->mlx, game->win, game->base.img_ptr, 0,0);
	mlx_string_put(game->mlx, game->win, 600,100,0xFFD700, ft_itoa(game->fps));
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
    double new_x = game->playerx;
    double new_y = game->playery;

    if (game->key_states[97])
        game->theta -= game->rotation_speed;
    if (game->key_states[100])
        game->theta += game->rotation_speed;

    if (game->theta >= 2 * PI)
        game->theta -= 2 * PI;
    else if (game->theta < 0)
        game->theta += 2 * PI;

    if (game->key_states[119])
    {
        new_x += game->speed * cos(game->theta);
        new_y += game->speed * sin(game->theta);
    }
    if (game->key_states[115])
    {
        new_x -= game->speed * cos(game->theta);
        new_y -= game->speed * sin(game->theta);
    }

    // Check boundaries before updating position
    if (new_x >= 0 && new_x < game->win_w && new_y >= 0 && new_y < game->win_h)
    {
        game->playerx = new_x;
        game->playery = new_y;
    }
}




int move(t_game *game)
{ 
    update_player_position(game);
    rotate_car_image(game);
    render_2d(game);
    // mlx_put_image_to_window(game->mlx, game->win, game->base.img_ptr, 0,0);
    limit_frame_rate(144);
    // usleep(5000);

    return 0;
}
