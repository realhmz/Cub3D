/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:07:46 by hboustaj          #+#    #+#             */
/*   Updated: 2025/01/24 15:07:47 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	searchar(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (true);
	while (str && str[i] && space_checker(str[i]))
		i++;
	if (str && str[i])
		return (false);
	return (true);
}

bool	help(char *temp, t_game *game, int *counter, char *var)
{
	if (++(*counter) > 2 && !searchar(temp))
		return (free(temp), false);
	if (searchar(temp) || !temp[0])
		return (free(temp), true);
	if (var[0] == 'F')
	{
		if (!(*counter))
			save_checker(game, 1, 'e');
		game->floor[*counter] = ft_atoi(temp);
	}
	else if (var[0] == 'C')
	{
		if (!(*counter))
			save_checker(game, 1, 'f');
		game->ceiling[*counter] = ft_atoi(temp);
	}
	free(temp);
	return (true);
}

bool	line_parser(t_game *game, char *var, char *str, int i)
{
	char	*temp;
	int		counter;
	int		start;

	counter = -1;
	while (str[++i])
	{
		while (str[i] && space_checker(str[i]))
			i++;
		start = i;
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (str[i] && !space_checker(str[i]) && str[i] != ',')
			return (err("invalide line of RGB color\n"), false);
		else
		{
			temp = ft_substr(str, start, i - start);
			if (!help(temp, game, &counter, var))
				return (false);
		}
		if (str[i + 1] && str[i + 1] == ',')
			i++;
	}
	return (true);
}

bool	color_checker(t_game *game, char *var, char *line, int i)
{
	int		start;
	char	*str;

	while (line[i] && space_checker(line[i]))
		i++;
	start = i;
	str = ft_substr(line, start, ft_strlen(line) - start);
	if (!str)
		return (false);
	if (!str[0] || !line_parser(game, var, str, -1))
		return (free(str), false);
	free(str);
	return (true);
}

bool	put_val(t_game *game, char *str, char *line, int i)
{
	if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
		|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
	{
		while (line[i] && space_checker(line[i]))
			i++;
		if (!path_checker(game, str, line, i))
			return (false);
		return (true);
	}
	else if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
	{
		if (!color_checker(game, str, line, i))
			return (false);
		return (true);
	}
	return (false);
}
