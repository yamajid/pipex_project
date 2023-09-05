/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamajid <yamajid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:23:06 by yamajid           #+#    #+#             */
/*   Updated: 2023/02/20 20:28:59 by yamajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_var
{
	int		pipe_fd[2];
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	char	**cmd1;
	char	**cmd2;
}			t_vars;

char		**find_path(char **env);
char		*find_command_path(char **env, char *cmd1);
char		**ft_split(char *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strchr(const char *s, int c);
int			ft_strncmp(char *s1, char *s2, size_t n);
size_t		ft_strlen(char *str);

#endif