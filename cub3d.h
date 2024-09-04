# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>

#define PI 3.14159265359
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

// libft
int	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);
