/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamajid <yamajid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:46:07 by yamajid           #+#    #+#             */
/*   Updated: 2023/02/20 22:27:28 by yamajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_all_fd(t_vars vars)
{
	close(vars.fd_in);
	close(vars.fd_out);
	close(vars.pipe_fd[0]);
	close(vars.pipe_fd[1]);
	perror("error");
	exit(1);
}

void	exec_cmd1(t_vars vars, char **env)
{
	close(vars.pipe_fd[0]);
	close(vars.fd_out);
	if (vars.fd_in == -1)
	{
		close(vars.pipe_fd[1]);
		exit(1);
	}
	if (dup2(vars.fd_in, STDIN_FILENO) < 0)
	{
		close(vars.fd_in);
		close(vars.pipe_fd[1]);
		perror("error");
		exit(1);
	}
	close(vars.fd_in);
	if (dup2(vars.pipe_fd[1], STDOUT_FILENO) < 0)
	{
		close(vars.pipe_fd[1]);
		perror("error");
		exit(1);
	}
	close(vars.pipe_fd[1]);
	if (execve(find_command_path(env, vars.cmd1[0]), vars.cmd1, env) < 0)
		perror("error");
	exit(1);
}

void	exec_cmd2(t_vars vars, char **env)
{
	close(vars.pipe_fd[1]);
	close(vars.fd_in);
	if (vars.fd_out == -1)
	{
		close(vars.pipe_fd[0]);
		exit(1);
	}
	if (dup2(vars.pipe_fd[0], STDIN_FILENO) < 0)
	{
		close(vars.pipe_fd[0]);
		close(vars.fd_out);
		perror("error");
		exit(1);
	}
	close(vars.pipe_fd[0]);
	if (dup2(vars.fd_out, STDOUT_FILENO) < 0)
	{
		close(vars.fd_out);
		perror("error");
		exit(1);
	}
	close(vars.fd_out);
	if (execve(find_command_path(env, vars.cmd2[0]), vars.cmd2, env) < 0)
		perror("error");
	exit(1);
}

void	process(t_vars vars, char **env)
{
	if (pipe(vars.pipe_fd) == -1)
	{
		perror("error ");
		close(vars.fd_in);
		close(vars.fd_out);
		exit(1);
	}
	vars.pid = fork();
	if (vars.pid == -1)
		close_all_fd(vars);
	if (vars.pid == 0)
		exec_cmd1(vars, env);
	vars.pid = fork();
	if (vars.pid == -1)
		close_all_fd(vars);
	if (vars.pid == 0)
		exec_cmd2(vars, env);
	close(vars.fd_in);
	close(vars.fd_out);
	close(vars.pipe_fd[0]);
	close(vars.pipe_fd[1]);
	while (wait(NULL) != -1)
		;
}

int	main(int argc, char **argv, char **env)
{
	t_vars	vars;

	if (argc != 5)
	{
		write(2, "expected 4 arguments\n", 21);
		return (1);
	}
	vars.cmd1 = ft_split(argv[2], ' ');
	vars.cmd2 = ft_split(argv[3], ' ');
	vars.fd_in = open(argv[1], O_RDONLY);
	if (vars.fd_in == -1)
		perror("ERROR");
	vars.fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (vars.fd_out == -1)
		perror("ERROR");
	process(vars, env);
	return (1);
}
