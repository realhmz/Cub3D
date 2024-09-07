/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:09:54 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/06 11:36:58 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flapy.h"

void    gravity(t_game *game)
{
    
    game->bird_y += game->gravity_force;
    game->bird_x += 0.05;
}
void apply_gravity(t_game *game)
{
    // Update bird's velocity based on gravity
    game->bird.velocity_y += game->acceleration_y;

    // Update bird's position based on the new velocity
    game->bird_y += game->bird.velocity_y;

    // If the bird reaches the bottom of the screen, stop it
    if (game->bird_y + 50 >= game->win_h)
    {
        game->bird_y = game->win_h - 50;
        game->bird.velocity_y = 0; // Stop the bird
    }

    // Prevent the bird from flying off the top of the screen
    if (game->bird_y < 0)
    {
        game->bird_y = 0;
        game->bird.velocity_y = 0;
    }
}