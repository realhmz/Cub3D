/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:17:18 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/06 11:35:23 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flapy.h"

// void update_player_position(t_game *game)
// {
  
// }

int handle_key(int keycode, t_game *game)
{
    if (keycode == 32)  // Assume SPACE_KEY is the jump key
    {
        game->bird.velocity_y = -12;  // Give the bird an upward boost
    }
    return 0;
}