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

typedef	struct s_fix
{
	double	step;
	double	inc_y;
	double	mid_y;
	double	curr_y_up;
	double	curr_y_down;
	double	visible_height;
	double	hit_y;
	double	tex_start;
	double	hit_up;
	double	hit_down;
	int		color;
} t_fix;


typedef struct s_dda
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	deltadist_x;
	double	deltadist_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	int		hit;
	int		side;
	int		i;
}   t_dda;

typedef struct s_line
{
	double	step;
	double	dx;
	double	dy;
	double	inc_x;
	double	inc_y;
	double	curr_x;
	double	curr_y;
}	t_line;

typedef struct s_ray
{
	double view;
	double min; 
	double angle_step;
	float ca;
	int ray;
	int line_height;
	int y_start;
	int y_end;
	double ray_angle;
}		t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		*floor;
	int		*ceiling;
	int		floor_color;
	int		ceiling_color;
	char	*save;
	char	pv;
	char	*key;
	float	view;
	int		Px;
	int		Py;
	int		map_width;
	int		map_height;
	double	hit_p;
	double	hit_p_y;
	double	distance;
	int		side;
	int		color;
	t_img	back;
	t_img	gun;
	t_img	wall_w;
	t_img	wall_e;
	t_img	wall_s;
	t_img	wall_n;
	t_dda	vars;
}			t_game;

// parsing
size_t			ftstrlen(const char *s);
char			*ftstrdup(const char *s1);
char			*my_strjoin(char *s1, char const *s2);
char			*get_next_line(int fd, bool flag);

bool	space_checker(char c);
bool	check_var(char *str);
bool	save_checker(t_game *game, bool flag, char c);
bool	afterline(char *line, int i);
bool	path_checker(t_game *game, char *var, char *line, int i);

bool	searchar(char *str);
bool	help(char *temp, t_game *game, int *counter, char *var);
bool	line_parser(t_game *game, char *var, char *str, int i);
bool	color_checker(t_game *game, char *var, char *line, int i);
bool	put_val(t_game *game, char *str, char *line, int i);

bool	handle_str(t_game *game, char *str, char *line, int i);
bool	fillin_data(t_game *game, char *line);
t_list	*fillin_map(char *line, t_list *lst);
bool	done(t_game *game);
bool	help2(char *line, int fd, t_game *game);

t_game			*parsing(char *arg);
void			ft_free(t_game *game);
bool			parse_map(t_game *game);

double	end_point_while(t_game *game, t_dda *vars);
void	dda_vars_init(t_game *game, double view, t_dda *vars);
int	is_wall_p(t_game *game, double x, double y);
// images
void			put_img_to_img(t_img dst, t_img src, int x, int y);
unsigned int	get_pixel_img(t_img img, int x, int y);
void			put_pixel_img(t_img img, int x, int y, int color);
t_img			new_file_img(char *path, t_game *game);
t_img			new_img(int w, int h, t_game *game);
// rendring
int				calc_darkness(double distance, int color);
double			end_point(t_game *game, double view);
double			rad(double angle);
//utils
int	calc_map_h(char **map);
int	max_width(char **map);
int	get_ceiling_color(int *rgb);
int	get_pv(char pv);
//moves
int is_wall(t_game *game, int x, int y);
int	draw_line_simple(int x1, int y1, int y2,t_game *game);
void	player_moves(t_game *game);
int	win(t_game *game);
#endif