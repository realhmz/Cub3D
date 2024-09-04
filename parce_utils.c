/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:02:38 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/04 12:03:00 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	player_pos(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y] && game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->playerx = x;
				game->playery = y;
			}
			x++;
		}
		y++;
	}
}

void	player_pos_real(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y] && game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->playerx = x * 50;
				game->playery = y * 50;
			}
			x++;
		}
		y++;
	}
}

void	exit_pos(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map && game->map[y])
	{
		x = 0;
		while (game->map[y] && game->map[y][x])
		{
			if (game->map[y][x] == 'E')
			{
				game->ex = x;
				game->ey = y;
			}
			x++;
		}
		y++;
	}
}

int	ft_count_char(char **str, char c)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	if (!str)
	{
		return (-1);
	}
	while (str && str[y])
	{
		x = 0;
		while (str[y] && str[y][x])
		{
			if (str[y][x] == c)
				i++;
			x++;
		}
		y++;
	}
	return (i);
}

int	count_newline(char *str, char **map)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			x++;
		i++;
	}
	i = 0;
	while (map && map[i])
		i++;
	if (i != x + 1)
		return (-1);
	return (x);
}