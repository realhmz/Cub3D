/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:08:20 by hboustaj          #+#    #+#             */
/*   Updated: 2025/01/24 15:08:21 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	space_checker(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

bool	check_var(char *str, t_game *game)
{
	if (!ft_strncmp(str, "NO", 2) && ft_strlen(str) == 2 && !game->north)
		return (true);
	if (!ft_strncmp(str, "SO", 2) && ft_strlen(str) == 2 && !game->south)
		return (true);
	if (!ft_strncmp(str, "WE", 2) && ft_strlen(str) == 2 && !game->west)
		return (true);
	if (!ft_strncmp(str, "EA", 2) && ft_strlen(str) == 2 && !game->east)
		return (true);
	if (!ft_strncmp(str, "F", 1) && ft_strlen(str) == 1
		&& game->floor[0] == -1)
		return (true);
	if (!ft_strncmp(str, "C", 1) && ft_strlen(str) == 1
		&& game->ceiling[0] == -1)
		return (true);
	err("ERROR : a non valid element detected\n");
	return (false);
}

bool	save_checker(t_game *game, bool flag, char c)
{
	char	*temp;
	char	*str;
	int		i;

	temp = game->save;
	if (flag)
	{
		i = ft_strlen(temp);
		if (i < 7 && !ft_strchr(temp, c))
		{
			temp[i] = c;
			return (true);
		}
	}
	i = -1;
	str = ft_strdup("abcdef");
	while (str[++i])
	{
		if (!ft_strchr(temp, str[i]))
			return (free(str), false);
	}
	return (free(str), true);
}

bool	afterline(char *line, int i)
{
	if (line && line[i])
		while (line[i] && space_checker(line[i]))
			i++;
	if (line[i])
		return (false);
	return (true);
}

bool	path_checker(t_game *game, char *var, char *line, int i)
{
	char	*path;
	int		start;

	start = i;
	while (line[i] && !space_checker(line[i]))
		i++;
	path = ft_substr(line, start, i - start);
	if (!afterline(line, i))
		return (free(path), false);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4)
		|| access(path, F_OK | R_OK) == -1)
	{
		err("ERROR : invalid path (.xpm).\n");
		return (false);
	}
	if (!ft_strncmp(var, "NO", 2) && save_checker(game, 1, 'a'))
		game->north = path;
	else if (!ft_strncmp(var, "SO", 2) && save_checker(game, 1, 'b'))
		game->south = path;
	else if (!ft_strncmp(var, "WE", 2) && save_checker(game, 1, 'c'))
		game->west = path;
	else if (!ft_strncmp(var, "EA", 2) && save_checker(game, 1, 'd'))
		game->east = path;
	return (true);
}
