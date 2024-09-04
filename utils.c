#include "cub3d.h"

int	check_file_name(char *str)
{
	int	i;
	int	fd;

	fd = open(str, O_RDONLY);
	if (!fd || fd == -1)
		return (-1);
	i = ft_strlen(str);
	i--;
	if (str[i] != 'b' || str[i - 1] != 'u' || str[i - 2] != 'c'
		|| str[i - 3] != '.' || !fd || fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	clear_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	error(t_game *game)
{
	free(game);
	write(1, "Error\n", 6);
	exit(0);
}

void	calc_win(t_game *game)
{
	int	i;

	i = 0;
	game->win_w = ft_strlen(game->map[0]) * 50;
	game->win_h = 0;
	while (game->map && game->map[i])
		i++;
	game->win_h = i * 50;
}

int	map_name(char *map)
{
	int	j;

	j = ft_strlen(map) - 1;
	if (j >= 4 && map && map[0] && map[j - 4] != '/')
	{
		if (map[j] == 'r' && map[j - 1] == 'e' && map[j - 2] == 'b'
			&& map[j - 3] == '.' && map[j - 4])
			return (1);
	}
	return (-1);
}
