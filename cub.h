#ifndef CUB_H
#define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"

# define BUFFER_SIZE 42
# define WIND_W 1280
# define WIND_H 720
# define MOVE_SPEED 4
# define M_PI 3.14159265358979323846
# define FOV 60
# define HALF_FOV  30
# define WALL_HEIGHT  100
# define SCREEN_HEIGHT  720
# define TILE_SIZE 100
# define PLAYER_BUFFER 10


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
}	t_img;

typedef struct s_dda
{
    double ray_dir_x;
    double ray_dir_y;
    double pos_x;
    double pos_y;
    int map_x;
    int map_y;
    double deltadist_x;
    double deltadist_y;
    int step_x;
    int step_y;
    double sidedist_x;
    double sidedist_y;
    int hit;
    int side;
    int i;
}   t_dda;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char    *north;
    char    *south;
    char    *west;
    char    *east;
    int     *floor;
    int     *ceiling;
	char	*save;
	char	*key;
    float     view;
    int     Px;
    int     Py;
    int     map_width;
    int     map_height;
    double  hit_p;
    double  hit_p_y;
	double distance;
    int     side;
    t_img   mini_map;
    t_img   back;
    t_img   gun;
    t_img   cros;
    t_img   wall_w;
    t_img   wall_e;
    t_img   wall_s;
    t_img   wall_n;
    t_dda   vars;
}               t_game;

size_t	ftstrlen(const char *s);
char	*ftstrdup(const char *s1);
char	*my_strjoin(char *s1, char const *s2);
char	*get_next_line(int fd, bool flag);
t_game  *parsing(char *arg);
void    ft_free(t_game *game);
bool	parse_map(t_game *game);

// images

void	put_img_to_img(t_img dst, t_img src, int x, int y);
unsigned int	get_pixel_img(t_img img, int x, int y);
void	put_pixel_img(t_img img, int x, int y, int color);
t_img	new_file_img(char *path, t_game *game);
t_img	new_img(int w, int h, t_game *game);
// rendring
int calc_darkness(t_game *game, double distance, int color);
double	end_point(t_game *game, double view);
double	rad(double angle);
#endif