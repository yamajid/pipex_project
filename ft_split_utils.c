/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamajid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:42:28 by yamajid           #+#    #+#             */
/*   Updated: 2023/02/26 18:42:31 by yamajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static int	count_word(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] && s[i] != c)
			i++;
		count++;
	}
	return (count);
}

static char	**free_go(char **ptr, size_t j)
{
	j--;
	while (j)
	{
		free(ptr[j]);
		j--;
	}
	free(ptr);
	return (NULL);
}

static int	word_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**ptr;
	int		i;
	int		count;
	int		j;

	if (!s)
		return (NULL);
	count = count_word(s, c);
	ptr = malloc((count + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		ptr[i] = (char *)malloc(sizeof(char) * (word_len(s, c) + 1));
		if (!ptr[i])
			return (free_go(ptr, i));
		j = 0;
		while (*s != '\0' && *s != c)
			ptr[i][j++] = *s++;
		ptr[i++][j] = '\0';
	}
	return (ptr[i] = NULL, ptr);
}
