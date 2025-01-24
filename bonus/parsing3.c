/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboustaj <hboustaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:07:53 by hboustaj          #+#    #+#             */
/*   Updated: 2025/01/24 15:07:54 by hboustaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	handle_str(t_game *game, char *str, char *line, int i)
{
	if (searchar(line))
		return (true);
	if (!check_var(str, game))
		return (false);
	if (!put_val(game, str, line, i))
		return (false);
	return (true);
}

bool	fillin_data(t_game *game, char *line)
{
	char	*str;
	int		start;
	int		i;

	i = 0;
	if (searchar(line))
		return (true);
	while (line[i] && space_checker(line[i]))
		i++;
	start = i;
	while (line[i] && !space_checker(line[i]))
		i++;
	str = ft_substr(line, start, i - start);
	if (!str)
		return (false);
	if (!str[0])
		return (free(str), true);
	if (!handle_str(game, str, line, i))
		return (free(str), false);
	return (free(str), true);
}

t_list	*fillin_map(char *line, t_list *lst)
{
	t_list	*temp;

	temp = ft_lstnew(ft_strdup(line));
	ft_lstadd_back(&lst, temp);
	return (lst);
}

bool	done(t_game *game)
{
	int	i;

	i = -1;
	if (!game->ceiling || !game->east || !game->west
		|| !game->north || !game->south || !game->floor)
	{
		err("ERROR : direction is missing\n");
		return (false);
	}
	while (++i <= 2)
	{
		if ((game->ceiling[i] < 0 || game->ceiling[i] > 255)
			|| (game->floor[i] < 0 || game->floor[i] > 255))
		{
			err("ERROR : RGB has invalid value\n");
			return (false);
		}
	}
	return (true);
}

bool	help2(char *line, int fd, t_game *game)
{
	if (!line)
		return (get_next_line(fd, 1), NULL);
	if (!save_checker(game, 0, 0) || !done(game))
		return (get_next_line(fd, 1), free(line), NULL);
	return (true);
}
