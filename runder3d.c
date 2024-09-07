/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runder3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:05:05 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/05 14:27:28 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"


void render_3d_projection(t_game *game)
{
    int w = game->win_w;
    int h = game->win_h;

    for (int x = 0; x < w; x++)
    {
        // Calculate the ray angle relative to the player's view angle
        double cameraX = 2 * x / (double)w - 1; // range from -1 to 1
        double rayDirX = cos(game->theta) + cameraX * cos(game->theta + M_PI / 2);
        double rayDirY = sin(game->theta) + cameraX * sin(game->theta + M_PI / 2);

        // Map position of the player
        int mapX = (int)(game->playerx / 50);
        int mapY = (int)(game->playery / 50);

        // Length of the ray from one x or y-side to the next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);

        // Initialize step and side distance
        int stepX, stepY;
        double sideDistX, sideDistY;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->playerx / 50 - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->playerx / 50) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->playery / 50 - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->playery / 50) * deltaDistY;
        }

        // Perform DDA to find wall hit
        int hit = 0, side;
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (game->map[mapY][mapX] == '1')
                hit = 1;
        }

        // Calculate distance to the point of impact
        double perpWallDist = (side == 0) ? (mapX - game->playerx / 50 + (1 - stepX) / 2) / rayDirX
                                          : (mapY - game->playery / 50 + (1 - stepY) / 2) / rayDirY;

        // Calculate height of the wall to be drawn on the screen
        int lineHeight = (int)(h / perpWallDist);

        // Calculate the top and bottom pixel of the wall slice
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h) drawEnd = h - 1;

        // Choose wall color based on side (or texture in the future)
        int color = (side == 0) ? 0xFF0000 : 0xAA0000; // Red for side 0, darker red for side 1

        // Draw the wall slice
        for (int y = drawStart; y < drawEnd; y++)
        {
            put_pixel_img(game->base, x, y, color);
        }

        // Draw the floor and ceiling
        for (int y = drawEnd; y < h; y++)
        {
            put_pixel_img(game->base, x, y, 0x00FF00); // Green for the floor
        }
        for (int y = 0; y < drawStart; y++)
        {
            put_pixel_img(game->base, x, y, 0x333333); // Gray for the ceiling
        }
    }

    // Render the final image to the window
    mlx_put_image_to_window(game->mlx, game->win, game->base.img_ptr, 0, 0);
}


#include <stdio.h>
#include <math.h>

void render_3d(t_game *game)
{
    int w = game->win_w;
    int h = game->win_h;

    for (int x = 0; x < w; x++)
    {
        double cameraX = 2 * x / (double)w - 1;
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        int mapX = (int)game->playerx;
        int mapY = (int)game->playery;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->playerx - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->playerx) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->playery - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->playery) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (mapX >= 0 && mapX < game->win_w / 50 && mapY >= 0 && mapY < game->win_h / 50)
            {
                if (game->map[mapY][mapX] == '1')
                    hit = 1;
            }
            else
            {
                break; // Exit if out of bounds
            }
        }

        if (hit)
        {
            if (side == 0)
                perpWallDist = (mapX - game->playerx + (1 - stepX) / 2) / rayDirX;
            else
                perpWallDist = (mapY - game->playery + (1 - stepY) / 2) / rayDirY;

            int lineHeight = (int)(h / perpWallDist);
            int drawStart = -lineHeight / 2 + h / 2;
            if (drawStart < 0)
                drawStart = 0;
            int drawEnd = lineHeight / 2 + h / 2;
            if (drawEnd >= h)
                drawEnd = h - 1;

            int wallColor = 0xFF0000;
            for (int y = drawStart; y < drawEnd; y++)
                put_pixel_img(game->base, x, y, wallColor);

            int floorColor = 0x00FF00;
            for (int y = drawEnd; y < h; y++)
                put_pixel_img(game->base, x, y, floorColor);
            
            for (int y = 0; y < drawStart; y++)
                put_pixel_img(game->base, x, y, 0x000000); // Ceiling
        }
        else
        {
            // Optionally, set the pixel to a background color if no wall hit
            for (int y = 0; y < h; y++)
                put_pixel_img(game->base, x, y, 0x000000);
        }
    }
    mlx_put_image_to_window(game->mlx, game->win, game->base.img_ptr, 0, 0);
}
