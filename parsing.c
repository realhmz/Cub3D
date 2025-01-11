
#include "cub.h"

bool    space_checker(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

bool    check_var(char *str)
{
    if (!ft_strncmp(str, "NO", 2) && ft_strlen(str) == 2)
        return (true);
    if (!ft_strncmp(str, "SO", 2) && ft_strlen(str) == 2)
        return (true);
    if (!ft_strncmp(str, "WE", 2) && ft_strlen(str) == 2)
        return (true);
    if (!ft_strncmp(str, "EA", 2) && ft_strlen(str) == 2)
        return (true);
    if (!ft_strncmp(str, "F", 1) && ft_strlen(str) == 1)
        return (true);
    if (!ft_strncmp(str, "C", 1) && ft_strlen(str) == 1)
        return (true);
    ft_putstr_fd("ERROR : a non valid element detected\n", 2);
    return (false);
}

bool    save_checker(t_game *game, bool flag, char c)
{
    char    *temp;
    char    *str;
    int     i;

    temp = game->save;
    if(flag)
    {   
        i = ft_strlen(temp);
        if(i < 7 && !ft_strchr(temp, c))
        {
            temp[i] = c;
            return (true);
        }
    }
    i = -1;
    str = ft_strdup("abcdef");
    while (str[++i])
    {
        if (!ft_strchr(temp, str[i]))
            return (free(str), false);
    }
    return (free(str), true);
}

bool    afterline(char *line, int i)
{
    if  (line && line[i])
        while (line[i] && space_checker(line[i]))
            i++;
    if (line[i])
        return (false);
    return (true);
}

bool    path_checker(t_game *game, char *var, char *line, int i)
{
    char    *path;
    int     start;

    start = i;
    while (line[i] && !space_checker(line[i]))
        i++;
    path = ft_substr(line, start, i - start);
    if (!afterline(line, i))
        return (free(path), false);
    if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4)
        || access(path, F_OK | R_OK) == -1)
    {
		ft_putstr_fd("ERROR : invalid path (.xpm).\n", 2);
        return (false);
    }
    if (!ft_strncmp(var, "NO", 2) && save_checker(game, 1, 'a'))
        game->north = path;
    else if (!ft_strncmp(var, "SO", 2) && save_checker(game, 1, 'b'))
        game->south = path;
    else if (!ft_strncmp(var, "WE", 2) && save_checker(game, 1, 'c'))
        game->west = path;
    else if (!ft_strncmp(var, "EA", 2) && save_checker(game, 1, 'd'))
        game->east = path;
    return (true);
}

bool    searchar(char *str)
{
    int i;

    i = 0;
    if (!str || !str[i])
        return (true);
    while (str && str[i] && space_checker(str[i]))
        i++;
    if (str && str[i])
        return (false);
    return (true);
}

bool    line_parser(t_game *game, char *var, char *str, int i)
{
    char    *temp;
    int     counter;
    int     start;

    counter = -1;
    while (str[++i])
    {
        while (str[i] && space_checker(str[i]))
            i++;
        start = i;
        while (str[i] && ft_isdigit(str[i]))
            i++;
        if (str[i] && !space_checker(str[i]) && str[i] != ',')
        {
            printf("invalide line of RGB color\n");
            return (false);
        }
        else
        {
            temp = ft_substr(str, start, i - start);
            if (++counter > 2 && !searchar(temp))
                return (free(temp), false);
            if(searchar(temp) || !temp[0])
                return (free(temp), true);
            if (var[0] == 'F')
            {
                if(!counter)
                    save_checker(game, 1, 'e');
                game->floor[counter] = ft_atoi(temp);
            }
            else if (var[0] == 'C')
            {
                if(!counter)
                    save_checker(game, 1, 'f');
                game->ceiling[counter] = ft_atoi(temp);
            }
            free(temp);
        }
        if(str[i + 1] && str[i + 1] == ',')
            i++;
    }
    return (true);
}

bool    color_checker(t_game *game, char *var, char *line, int i)
{
    int     start;
    char    *str;

    while (line[i] && space_checker(line[i]))
        i++;
    start = i;
    str = ft_substr(line, start, ft_strlen(line) - start);
    if (!str)
        return (false);
    if (!str[0] || !line_parser(game, var, str, -1))
        return (free(str), false);
    free(str);
    return (true);
}

bool    put_val(t_game *game, char *str, char *line, int i)
{
    if (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
        || !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
    {
        while (line[i] && space_checker(line[i]))
            i++;
        if (!path_checker(game, str, line, i))
            return (false);
        return (true);
    }
    else if (!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
    {
        if (!color_checker(game, str, line, i))
            return (false);
        return (true);
    }
    return (false);
}

bool    handle_str(t_game *game, char *str, char *line, int i)
{
    if (searchar(line))
        return (true);
    if (!check_var(str))
        return (false);
    if (!put_val(game, str, line, i))
        return (false);
    return (true);
}

bool    fillin_data(t_game *game, char *line)
{
    char    *str;
    int     start;
    int     i;

    i = 0;
    if (searchar(line))
        return (true);
    while (line[i] && space_checker(line[i]))
        i++;
    start = i;
    while (line[i] && !space_checker(line[i]))
        i++;
    str = ft_substr(line, start, i - start);
    if (!str)
        return (false);
    if (!str[0])
        return (free(str), true);
    if (!handle_str(game, str, line, i))
        return (free(str), false);
    return (free(str), true);
}

t_list    *fillin_map(char *line, t_list *lst)
{
    t_list *temp;

    temp = ft_lstnew(ft_strdup(line));
    ft_lstadd_back(&lst, temp);
    return (lst);  
}

bool    done(t_game *game)
{
    int i;

    i = -1;
    if(!game->ceiling || !game->east || !game->west 
        || !game->north || !game->south || !game->floor)
    {
        ft_putstr_fd("ERROR : direction is missing\n", 2);
        return (false);
    }
    while(++i <= 2)
    {
        if((game->ceiling[i] < 0 || game->ceiling[i] > 255)
            || (game->floor[i] < 0 || game->floor[i] > 255))
        {
            ft_putstr_fd("ERROR : RGB has invalid value\n", 2);
            return (false);
        }
    }
    return (true);
}

t_list    *parse_args(t_game *game, char *arg)
{
    char    *line;
    int     fd;
    t_list *lst;

    fd = open(arg, O_RDONLY);
    line = get_next_line(fd, 0);
    if (!line)
        return (get_next_line(fd, 1), NULL);
    while (line && !save_checker(game, 0, 0))
    {
        if(!fillin_data(game, line))
            return (get_next_line(fd, 1), free(line), NULL);
        free(line);
        line = get_next_line(fd, 0);
    }
    if (!line)
        return (get_next_line(fd, 1), NULL);
    if (!save_checker(game, 0, 0) || !done(game))
        return (get_next_line(fd, 1), free(line), NULL);
    lst = NULL;
    while (line)
    {
        lst = fillin_map(line, lst);
        if (!lst)
            return(get_next_line(fd, 1), NULL);
        free (line);
        line = get_next_line(fd, 0);
    }
    return (lst);
}

void    free_lst(t_list **lst)
{
    t_list *temp;
    t_list *ptr;

    ptr = *lst;
    temp = ptr->next;
    while(ptr)
    {
        free(ptr->content);
        free(ptr);
        ptr = temp;
        if (temp)
            temp = temp->next;
    }
}

bool    convert_to_arr(t_game *game, t_list **lst)
{
    int size;
    t_list *temp;

    temp = *lst;
    size = ft_lstsize(*lst);
    game->map = ft_calloc(sizeof(char *), size + 2);
    if(!game->map)
        return (false);
    size = 0;
    while (temp && searchar(temp->content))
        temp = temp->next;
    while (temp && !searchar(temp->content))
    {
        game->map[size] = ft_substr(temp->content, 0, ft_strlen(temp->content) - 1);
        temp = temp->next;
        size++;
    }
    game->map[size] = NULL;
    free_lst(lst);
    return (true);
}

// void    printer(t_game *game)
// {
//     int i;

//     i = -1;
//     printf("\n#################################################\n");
//     printf("\nnorth = [%s]\n", game->north);
//     printf("south = [%s]\n", game->south);
//     printf("west = [%s]\n", game->west);
//     printf("east = [%s]\n", game->east);
//     printf("floor = [%d] [%d] [%d]\n", game->floor[0], game->floor[1], game->floor[2]);
//     printf("ceiling = [%d] [%d] [%d]\n", game->ceiling[0], game->ceiling[1], game->ceiling[2]);
//     while(game->map && game->map[++i])
//         printf("map[%d] = [%s]\n", i, game->map[i]);
//     printf("\n#################################################\n");
// }

bool    check_lst(t_list *lst)
{
    t_list  *ptr;

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
            return(false);
        }
    }
    return (true);
}

t_game  *parsing(char *arg)
{
    t_game  *game;
    t_list  *lst;

	if (ft_strncmp(arg + ft_strlen(arg) - 4, ".cub", 4)
        || access(arg, F_OK | R_OK) == -1)
    {
		ft_putstr_fd("Error : Your map file is invalid.\n", 2);
        return (NULL);
    }
    game = ft_calloc(1, sizeof(t_game));
    // game = malloc(sizeof(t_game));
    if (!game)
        return (NULL);
    game->floor = ft_calloc (sizeof(int), 4);
    game->ceiling = ft_calloc (sizeof(int), 4);
    game->save = ft_calloc(8, 1);
    ft_memset(game->ceiling, -1, 16);
    ft_memset(game->floor, -1, 16);
    lst = parse_args(game, arg);
    if (!lst)
        return (ft_free(game), NULL);
    if(!check_lst(lst))
        return (free_lst(&lst), ft_free(game), NULL);
    convert_to_arr(game, &lst);
    if (!game->map)
        return (NULL);
    // printer(game);
    return (game);
}
