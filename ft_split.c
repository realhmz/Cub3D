/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:01:04 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/04 11:05:37 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

static int	wrds_count(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] != sep)
		{
			count++;
			while (str[i] != sep && str[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*wrd_malloc(const char *str, char sep)
{
	int		i;
	char	*word;

	i = 0;
	while (str && str[i] && str[i] != sep)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, i + 1);
	return (word);
}

static char	**remove_leaks(char **buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		free(buff[i]);
		i++;
	}
	free(buff);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**buff;

	i = 0;
	j = 0;
	buff = (char **)malloc(sizeof(char *) * (wrds_count(s, c) + 1));
	if (!buff)
		return (NULL);
	while (s && s[i])
	{
		if (s[i] != c)
		{
			buff[j] = wrd_malloc(s + i, c);
			if (!buff[j])
				return (remove_leaks(buff));
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	buff[j] = NULL;
	return (buff);
}