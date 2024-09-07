/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:51:08 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/05 14:36:42 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
#include <math.h>

#define FOV 60.0    // Field of view in degrees
#define NUM_RAYS 60 // Number of rays to cast

void raycasting(t_game *game)
{
    double ray_angle;
    double ray_x, ray_y;
    int map_x, map_y;
    int hit;

    double start_angle = game->theta - (FOV / 2.0) * (PI / 180.0); // Start angle in radians
    double angle_step = FOV * (PI / 180.0) / NUM_RAYS; // Angle between each ray

    for (int i = 0; i < NUM_RAYS; i++)
    {
        ray_angle = start_angle + i * angle_step;

        ray_x = game->playerx;
        ray_y = game->playery;

        hit = 0;

        while (!hit)
        {
            ray_x += cos(ray_angle);
            ray_y += sin(ray_angle);

            map_x = (int)(ray_x / 50); // Assuming each map square is 50x50 pixels
            map_y = (int)(ray_y / 50);

            // Check if the ray hits a wall
            if (game->map[map_y][map_x] == '1')
            {
                hit = 1;
                // Draw the ray up to this point
                bresenham_line(game, game->playerx, game->playery, (int)ray_x, (int)ray_y, 0xFF0000); // Red line
            }
        }
    }
}

void render_3d_car(t_game *game)
{
    int w = game->win_w;
    int h = game->win_h;

    // Calculate the car's position in 3D space
    double car_x = game->playerx;
    double car_y = game->playery;

    // Calculate relative position to the camera
    double relCarX = car_x - game->playerx;
    double relCarY = car_y - game->playery;

    // Calculate the 2D projection of the car
    double carDirX = relCarX * game->dirX + relCarY * game->dirY;
    double carDirY = relCarX * -game->dirY + relCarY * game->dirX;

    int carScreenX = (int)((w / 2) + (carDirX * w / 2) / carDirY);
    int carScreenY = (int)((h / 2) - (carDirY * h / 2) / carDirY);

    // Draw the car image
    mlx_put_image_to_window(game->mlx, game->win, game->car.img_ptr, carScreenX, carScreenY);
}