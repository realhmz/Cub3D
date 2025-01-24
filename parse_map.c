/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:08:27 by hboustaj          #+#    #+#             */
/*   Updated: 2025/01/24 15:08:28 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_free(t_game *game)
{
	int	i;

	free(game->save);
	free(game->ceiling);
	free(game->floor);
	if (game->east)
		free(game->east);
	if (game->south)
		free(game->south);
	if (game->north)
		free(game->north);
	if (game->west)
		free(game->west);
	i = -1;
	if (game->map)
	{
		if (game->map[++i])
			while (game->map && game->map[i])
				free(game->map[i++]);
		free(game->map);
	}
	free(game);
}

int	fillemptyspace(t_game *game, int j, char *s)
{
	int		i;

	while (game->map && game->map[++j])
	{
		i = -1;
		s = game->map[j];
		while (s && s[++i])
		{
			if (s[i] == ' ')
				s[i] = '1';
			if (s[i] != '1' && s[i] != '0')
			{
				if ((s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
					&& !game->px && !game->py)
				{
					game->pv = s[i];
					game->px = i * TILE_SIZE + 25;
					game->py = j * TILE_SIZE + 25;
				}
				else
					return (err("Error: invalid map\n"), false);
			}
		}
	}
	return (j);
}

bool	checkwall(char **map, int j)
{
	int	size;
	int	len;

	size = ft_strlen(map[j - 1]) - 1;
	len = ft_strlen(map[j + 1]) - 1;
	if (size > len)
		size = len;
	len = ft_strlen(map[j]) - 1;
	if (map[j][0] != '1' || map[j][len] != '1')
		return (false);
	if (len > size)
	{
		while ((--len > size))
		{
			if (map[j][len] != '1')
				return (false);
		}
	}
	return (true);
}

bool	closedmap(t_game *game, int len)
{
	int		i;
	int		j;
	char	*s;

	j = -1;
	while (game->map && game->map[++j])
	{
		s = game->map[j];
		if ((!j || j == (len - 1)))
		{
			i = -1;
			while (s && s[++i])
				if (s[i] != '1')
					return (err("Error: invalid map\n"), false);
		}
		else
			if (!checkwall(game->map, j))
				return (err("Error: invalid map\n"), false);
	}
	return (true);
}

bool	parse_map(t_game *game)
{
	int	len;

	len = fillemptyspace(game, -1, NULL);
	if (!len)
		return (false);
	if (!closedmap(game, len))
		return (false);
	if (!game->pv)
		return (err("Error: Player is not exist\n"), false);
	return (true);
}
