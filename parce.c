#include "cub3d.h"

int	parcing(t_game *game, char *map)
{
	if (map_name(map) == -1)
		return (-1);
	if (read_map(game, map) == -1)
	{
		clear_map(game->map);
		return (-1);
	}
	if (parce_map(game->map) == -1 || map_walls(game) == -1)
	{
		clear_map (game->map);
		return (-1);
	}
	player_pos(game);
	exit_pos(game);
	return (0);
}

int	read_map(t_game *game, char *map)
{
	int		fd;
	char	*buff;
	int		readed;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		exit(error(game));
	buff = malloc(1001);
	readed = read(fd, buff, 1000);
	buff[readed] = '\0';
	if (read(fd, buff, 10))
	{
		free(buff);
		return (-1);
	}
	close (fd);
	game->map = ft_split(buff, '\n');
	if (count_newline(buff, game->map) == -1)
	{
		free(buff);
		return (-1);
	}
	free(buff);
	return (0);
}

int	map_walls(t_game *game)
{
	int	x;
	int	y;
	int	hight;
	int	len;

	y = 0;
	len = ft_strlen(game->map[y]);
	hight = -1;
	while (game->map && game->map[y])
	{
		if (game->map[y][0] != '1' || game->map[y][len - 1] != '1')
			return (-1);
		y++;
		hight++;
	}
	x = 0;
	while (game->map[hight][x] && game->map[0][x])
	{
		if (game->map[hight][x] != '1' || game->map[0][x] != '1')
			return (-1);
		x++;
	}
	return (0);
}

int	is_wrong_char(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		j = 0;
		while (str[i] && str[i][j])
		{
			if (str[i][j] != 'P' && str[i][j] != 'E' && str[i][j] != 'C'
				&& str[i][j] != '1' && str[i][j] != '0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	parce_map(char **str)
{
	int	y;
	int	len;

	y = 0;
	if (!str)
		return (-1);
	if (ft_count_char(str, 'P') != 1 || ft_count_char(str, 'E') != 1
		|| ft_count_char(str, 'C') < 1)
		return (-1);
	if (is_wrong_char(str) != 0)
		return (-1);
	len = ft_strlen(str[0]);
	while (str && str[y])
	{
		if (ft_strlen(str[y]) != len)
		{
			return (-1);
		}
		y++;
	}
	return (0);
}
