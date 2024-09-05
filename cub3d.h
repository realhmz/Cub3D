# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
#include <pthread.h>

#define PI 3.14159265359
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

typedef struct s_asset
{
	t_img	*e;
}t_asset;

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	char	**map;
	float	playerx;
	float	playery;
	int		ex;
	int		ey;
	int		win_h;
	int		win_w;
	int		*key_states;
	float	theta;
	float	speed;
	float	rotation_speed;
	long	fps;
	t_asset	*asset;
	pthread_t		render_thread;
	pthread_t		rotation_thread;
	pthread_t		render2d_thread;
	pthread_mutex_t	map_mutex;
	pthread_mutex_t	rotation_mutex;
	t_img	base;
	t_img	back;
	t_img	wall;
	t_img	car;
}		t_game;



// parsing functions

int	parcing(t_game *game, char *map);
int	parce_map(char **str);
int	check_file_name(char *str);
int	is_wrong_char(char **str);
int	map_walls(t_game *game);
int	read_map(t_game *game, char *map);
int	count_newline(char *str, char **map);
int	ft_count_char(char **str, char c);
void	exit_pos(t_game *game);
void	player_pos_real(t_game *game);
void	player_pos(t_game *game);
char	*ft_strdup(char *s);
char	**map_dup(char **map);
void	error_fill(t_game *game, char **map);
int	flood_fill(t_game *game);
void	check_path(int x, int y, char **map, char c);
void	check_path_exit(int x, int y, char **map, char c);
int	check_fill(char **map, char c);
void	calc_win(t_game *game);
int	error(t_game *game);
void	clear_map(char **map);
int	map_name(char *map);

//moves
int move(t_game *game);
void update_player_position(t_game *game);
int key_release(int keycode, t_game *game);
int key_press(int keycode, t_game *game);
void render_2d(t_game *game);
// void rotate_car_image(t_game *game, double theta);
void clear_img(t_img *img, int width, int height, int color);
void	load_map(t_game *game);
// libft
int	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);


// img functions
void	put_img_to_img(t_img dst, t_img src, int x, int y);
t_img	new_file_img(char *path, t_game *window);
t_img	new_img(int w, int h, t_game *window);
void	put_pixel_img(t_img img, int x, int y, int color);
unsigned int	get_pixel_img(t_img img, int x, int y);
void	put_nimg_to_img(t_img dst, t_img src, int x, int y, int w, int h);


// fps
void count_fps(t_game *game);
void limit_frame_rate(int target_fps);

//collition
int	check_collision(int y, int x, int py, int px);

// tiles
void	edge_assets(t_game *game);
void	put_edge(t_game *game, t_img *e, int x, int y);
void	ft_put(t_game *game, t_img img, int x, int y);

void rotate_car_image(t_game *game);
