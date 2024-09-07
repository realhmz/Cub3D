/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flapy.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:52:44 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/06 11:59:08 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "./minilibx-linux/mlx.h"
# include <time.h>
# include  <pthread.h>

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		line_len;
	int		endian;
	void	*win;
    float   velocity_y;
}	t_img;

typedef struct s_game{
    void    *mlx;
    void    *win;
    float   bird_x;
    float   bird_y;
    float   gravity_force;
    char    **map;
    int     last_x;
    int     last_y;
    int     win_h;
    int     win_w;
    t_img   back;
    t_img   sky;
    t_img   wall;
    t_img   bird;
    t_img   bot;
    t_img   floor1;
    t_img   floor2;
    t_img   center;
    t_img   up;
    float   acceleration_y;
    int     wall_offset;
    pthread_t   rendering;
}       t_game;




//
void    draw_bird(t_game *game);
int render(t_game *game);
void	put_nimg_to_img(t_img dst, t_img src, int x, int y, int w, int h);
void	put_img_to_img(t_img dst, t_img src, int x, int y);
t_img	new_file_img(char *path, t_game *window);
t_img	new_img(int w, int h, t_game *window);



//parse
int	read_map(t_game *game, char *map);
char	**ft_split(char const *s, char c);
void	calc_win(t_game *game);
char	*ft_strdup(char *s);
int	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int	count_newline(char *str, char **map);
void	player_pos_real(t_game *game);
void	player_pos_real(t_game *game);
void	ft_put(t_game *game, t_img img, int x, int y);

void limit_frame_rate(int target_fps);\

int	collition(t_game *game, int py, int px);
int	check_collision(int y, int x, int py, int px);
void    gravity(t_game *game);
void apply_gravity(t_game *game);
int handle_key(int keycode, t_game *game);