/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:19:07 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/05 13:01:50 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wich_edge(t_game *game, int x, int y)
{
	int	up;
	int	down;
	int	right;
	int	left;
	int	i;

	up = 0;
	down = 0;
	right = 0;
	left = 0;
	if (game->map[x] && (game->map[x][y] == '0' ))
	{
		i = 0;
		if (y < (game->win_w -1) / 50 && game->map[x][y + 1] != '0')
			right = 1;
		if (x > 0 / 50 && game->map[x - 1][y] != '0')
			up = 2;
		if (y > 0 && game->map[x][y - 1] != '0')
			left = 4;
		if (x < (game->win_h - 1) / 50 && game->map[x + 1][y] != '0')
			down = 8;
		i = left + right + down + up;
		return (i);
	}
	return (-1);
}
void	ft_put(t_game *game, t_img img, int x, int y)
{
	put_img_to_img(game->back, img, x, y);
}

void	put_edge(t_game *game, t_img *e, int x, int y)
{
	int	i;

	i = wich_edge(game, y, x);
	// ft_put(game, game->asset->floor, x * 50, y * 50);
	if (i == -1)
		return ;
	if (game->map[y][x] == '0' && i != -1)
		ft_put(game, e[i], x * 50, y * 50);
}

static void	more(t_game *game)
{
	game->asset->e[0] = new_file_img("./tiles/0.xpm",
			game);
	game->asset->e[1] = new_file_img("./tiles/1.xpm",
			game);
	game->asset->e[2] = new_file_img("./tiles/2.xpm",
			game);
	game->asset->e[12] = new_file_img("./tiles/12.xpm",
			game);
	game->asset->e[13] = new_file_img("./tiles/13.xpm",
			game);
	game->asset->e[14] = new_file_img("./tiles/14.xpm",
			game);
	game->asset->e[15] = new_file_img("./tiles/15.xpm",
			game);
}

void	edge_assets(t_game *game)
{
	more(game);
	game->asset->e[3] = new_file_img("./tiles/3.xpm",
			game);
	game->asset->e[4] = new_file_img("./tiles/4.xpm",
			game);
	game->asset->e[5] = new_file_img("./tiles/5.xpm",
			game);
	game->asset->e[6] = new_file_img("./tiles/6.xpm",
			game);
	game->asset->e[7] = new_file_img("./tiles/7.xpm",
			game);
	game->asset->e[8] = new_file_img("./tiles/8.xpm",
			game);
	game->asset->e[9] = new_file_img("./tiles/9.xpm",
			game);
	game->asset->e[10] = new_file_img("./tiles/10.xpm",
			game);
	game->asset->e[11] = new_file_img("./tiles/11.xpm",
			game);
}