/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamajid <yamajid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:31:29 by yamajid           #+#    #+#             */
/*   Updated: 2023/02/20 20:54:05 by yamajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;
	size_t			i;

	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (-1);
	dst = (unsigned char *)s1;
	src = (unsigned char *)s2;
	i = 0;
	while ((dst[i] || src[i]) && i < n)
	{
		if (dst[i] != src[i])
			return (dst[i] - src[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = '/';
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
	return (ptr);
}

int	ft_strchr(const char *s, int c)
{
	int		i;
	char	*s1;

	s1 = (char *)s;
	i = 0;
	while (s1[i])
	{
		if (s1[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	**find_path(char **env)
{
	char	*tmp;

	tmp = "PATH=";
	while (*env)
	{
		if (ft_strncmp(tmp, *env, 5) == 0)
		{
			return (ft_split(*env + 5, ':'));
		}
		env++;
	}
	return (NULL);
}

char	*find_command_path(char **env, char *cmd1)
{
	char	*cmd;
	char	**str;
	int		i;

	i = 0;
	if (ft_strchr(cmd1, '/') == 1)
		return (cmd1);
	str = find_path(env);
	while (str[i])
	{
		cmd = ft_strjoin(str[i], cmd1);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			free(cmd);
		i++;
	}
	perror("ERROR:command not found");
	return (NULL);
}
