/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:00:49 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/04 11:00:50 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	error_fill(t_game *game, char **map)
{
	clear_map(map);
	clear_map(game->map);
	map = NULL;
	game->map = NULL;
}

int	flood_fill(t_game *game)
{
	char	**tmp;

	tmp = NULL;
	tmp = map_dup(game->map);
	check_path(game->playerx, game->playery, tmp, 'C');
	if (check_fill(tmp, 'C') == -1)
	{
		error_fill(game, tmp);
		return (-1);
	}
	check_path_exit(game->playerx, game->playery, tmp, 'E');
	if (check_fill(tmp, 'E') == -1)
	{
		error_fill(game, tmp);
		return (-1);
	}
	clear_map(tmp);
	tmp = NULL;
	return (0);
}

void	check_path(int x, int y, char **map, char c)
{
	if (map && map[y] && map[y][x])
	{
		if (map[y][x] == '0' || map[y][x] == c || map[y][x] == 'P')
		{
			map[y][x] = 'V';
			check_path(x + 1, y, map, c);
			check_path(x - 1, y, map, c);
			check_path(x, y + 1, map, c);
			check_path(x, y - 1, map, c);
		}
	}
}

void	check_path_exit(int x, int y, char **map, char c)
{
	if (map && map[y] && map[y][x])
	{
		if (map[y][x] == '0' || map[y][x] == c || map[y][x] == 'V')
		{
			map[y][x] = '1';
			check_path_exit(x + 1, y, map, c);
			check_path_exit(x - 1, y, map, c);
			check_path_exit(x, y + 1, map, c);
			check_path_exit(x, y - 1, map, c);
		}
	}
}

int	check_fill(char **map, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map && map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == c)
				return (-1);
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}