#include "cub.h"

t_list	*parse_args(t_game *game, char *arg, t_list *lst)
{
	char	*line;
	int		fd;

	fd = open(arg, O_RDONLY);
	line = get_next_line(fd, 0);
	if (!line)
		return (get_next_line(fd, 1), NULL);
	while (line && !save_checker(game, 0, 0))
	{
		if (!fillin_data(game, line))
			return (get_next_line(fd, 1), free(line), NULL);
		free(line);
		line = get_next_line(fd, 0);
	}
	if (!help2(line, fd, game))
		return (NULL);
	while (line)
	{
		lst = fillin_map(line, lst);
		if (!lst)
			return (get_next_line(fd, 1), NULL);
		free(line);
		line = get_next_line(fd, 0);
	}
	return (lst);
}

void	free_lst(t_list **lst)
{
	t_list	*temp;
	t_list	*ptr;

	ptr = *lst;
	temp = ptr->next;
	while (ptr)
	{
		free(ptr->content);
		free(ptr);
		ptr = temp;
		if (temp)
			temp = temp->next;
	}
}

bool	convert_to_arr(t_game *game, t_list **lst)
{
	int		size;
	t_list	*temp;

	temp = *lst;
	size = ft_lstsize(*lst);
	game->map = ft_calloc(sizeof(char *), size + 2);
	if (!game->map)
		return (false);
	size = 0;
	while (temp && searchar(temp->content))
		temp = temp->next;
	while (temp && !searchar(temp->content))
	{
		game->map[size]
			= ft_substr(temp->content, 0, ft_strlen(temp->content) - 1);
		temp = temp->next;
		size++;
	}
	game->map[size] = NULL;
	free_lst(lst);
	if (!game->map)
		return (false);
	return (true);
}

bool	check_lst(t_list *lst)
{
	t_list	*ptr;

	ptr = lst;
	while (ptr && searchar(ptr->content))
		ptr = ptr->next;
	if (!ptr)
	{
		ft_putstr_fd("ERROR : there is no map\n", 2);
		return (false);
	}
	while (ptr && !searchar(ptr->content))
		ptr = ptr->next;
	if (ptr)
	{
		while (ptr && searchar(ptr->content))
			ptr = ptr->next;
		if (ptr)
		{
			ft_putstr_fd("ERROR : detecting characters after the map\n", 2);
			return (false);
		}
	}
	return (true);
}

t_game	*parsing(char *arg)
{
	t_game	*game;
	t_list	*lst;

	if (ft_strncmp(arg + ft_strlen(arg) - 4, ".cub", 4)
		|| access(arg, F_OK | R_OK) == -1)
	{
		ft_putstr_fd("Error : Your map file is invalid.\n", 2);
		return (NULL);
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->floor = ft_calloc (sizeof(int), 4);
	game->ceiling = ft_calloc (sizeof(int), 4);
	game->save = ft_calloc(8, 1);
	ft_memset(game->ceiling, -1, 16);
	ft_memset(game->floor, -1, 16);
	lst = parse_args(game, arg, NULL);
	if (!lst)
		return (ft_free(game), NULL);
	if (!check_lst(lst))
		return (free_lst(&lst), ft_free(game), NULL);
	if (!convert_to_arr(game, &lst))
		return (NULL);
	return (game);
}
