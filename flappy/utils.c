/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:13:49 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/06 10:44:57 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flapy.h"

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

int	read_map(t_game *game, char *map)
{
	int		fd;
	char	*buff;
	int		readed;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		exit(1);
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == '\0')
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**map_dup(char **map)
{
	char	**dup;
	int		i;

	i = 0;
	while (map && map[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (map && map[i])
	{
		dup[i] = ft_strdup(map[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

char	*ft_strdup(char *s)
{
	char	*str;
	size_t	index;
	size_t	lenth;

	lenth = ft_strlen(s);
	index = 0;
	if (!s)
		return (NULL);
	str = (char *)malloc(lenth + 1);
	if (!str)
		return (NULL);
	while (index < lenth)
	{
		str[index] = s[index];
		index++;
	}
	str[index] = '\0';
	return (str);
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
				game->bird_x = x * 50;
				game->bird_y = y * 50;
			}
			x++;
		}
		y++;
	}
}

void	ft_put(t_game *game, t_img img, int x, int y)
{
	put_img_to_img(game->back, img, x, y);
}

void limit_frame_rate(int target_fps)
{
    static struct timespec last_frame_time;
    struct timespec current_time;
    long sleep_time;
    int nano_seconds_per_frame = 1000000000 / target_fps;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    // Calculate the elapsed time since the last frame
    long elapsed_time = (current_time.tv_sec - last_frame_time.tv_sec) * 1000000000L
                        + (current_time.tv_nsec - last_frame_time.tv_nsec);

    // Calculate how much time to sleep until the next frame
    sleep_time = nano_seconds_per_frame - elapsed_time;

    // If we need to sleep, do it
    if (sleep_time > 0)
    {
        struct timespec sleep_duration;
        sleep_duration.tv_sec = sleep_time / 1000000000;
        sleep_duration.tv_nsec = sleep_time % 1000000000;
        nanosleep(&sleep_duration, NULL);
    }

    // Update the last frame time
    clock_gettime(CLOCK_MONOTONIC, &last_frame_time);
}