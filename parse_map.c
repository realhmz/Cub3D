
#include "cub.h"

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
					&& !game->Px && !game->Py)
				{
					game->Px = i * TILE_SIZE + 25;
					game->Py = j * TILE_SIZE + 25;
				}
				else
					return (ft_putstr_fd("Error: invalid map\n", 2), false);
			}
		}
	}
	return (j);
}

bool	checkwall(char **map, int j)
{
	int size;
	int len;

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
					return (ft_putstr_fd("Error: invalid map\n", 2), false);
		}
		else
			if (!checkwall(game->map, j))	
				return (ft_putstr_fd("Error: invalid map\n", 2), false);
	}
	return (true);
}

bool	parse_map(t_game *game)
{
	int len;
	len = fillemptyspace(game, -1, NULL);
	if (!len)
		return (false);
	if (!closedmap(game, len))
		return (false);
	return (true);
}