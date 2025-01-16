/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:07:16 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 18:09:53 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ;

void	duplicate_std(int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) < 0)
		exit_error("dup2 error");
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		exit_error("dup2 error");
	close(in_fd);
	close(out_fd);
}

int	is_exec(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

void	exec_cmd(char *cmd, int in_fd, int out_fd)
{
	char	**args;
	char	*path;

	duplicate_std(in_fd, out_fd);
	args = ft_split(cmd, ' ');
	if (!args)
		exit_error("split error");
	if (!access(args[0], F_OK))
		path = ft_strdup(args[0]);
	else
		path = find_path(args[0]);
	if (!path)
	{
		free_split(args);
		exit_wcode("command not found\n", 127);
	}
	if (!is_exec(path))
	{
		free_split(args);
		exit_wcode("command not executable\n", 126);
	}
	execve(path, args, environ);
	free(path);
	free_split(args);
	exit_error("execve error");
}

void	execute_first_cmd(t_pipex *pipex)
{
	int	infile;

	infile = open(pipex->argv[1], O_RDONLY);
	if (infile < 0)
		exit_error("Infile error");
	close(pipex->pipe_fd[0]);
	exec_cmd(pipex->argv[2], infile, pipex->pipe_fd[1]);
}

void	execute_second_cmd(t_pipex *pipex)
{
	int	outfile;

	outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		exit_error("Outfile error");
	close(pipex->pipe_fd[1]);
	exec_cmd(pipex->argv[3], pipex->pipe_fd[0], outfile);
}
