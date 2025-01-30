/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:28:37 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 17:28:38 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

extern char	**environ;

void	exec_cmd(char *cmd, int in_fd, int out_fd, t_cleanup *cleanup_data)
{
	char	**args;
	char	*path;

	duplicate_std(in_fd, out_fd);
	args = ft_split(cmd, ' ');
	if (!args)
		cleanup_error("malloc", cleanup_data, EXIT_FAILURE);
	if (!access(args[0], F_OK | X_OK))
		path = ft_strdup(args[0]);
	else
		path = find_path(args[0]);
	if (!path)
	{
		free_split(args);
		cleanup_error("command not found", cleanup_data, 127);
	}
	if (!is_exec(path))
	{
		free_split(args);
		cleanup_error("command not executable", cleanup_data, 126);
	}
	execve(path, args, environ);
	free(path);
	free_split(args);
	cleanup_error("execve", cleanup_data, EXIT_FAILURE);
}

void	first_command(t_pipe_data *data, t_cleanup *clean_data)
{
	char	*infile_path;
	char	*cmd;
	int		*pfd;
	int		infile;

	infile_path = data->argv[1];
	cmd = data->argv[2];
	pfd = data->pfd;
	infile = open(infile_path, O_RDONLY);
	if (infile < 0)
		cleanup_error("open infile", clean_data, EXIT_FAILURE);
	close(pfd[0]);
	exec_cmd(cmd, infile, pfd[1], clean_data);
}

void	last_command(t_pipe_data *data, t_cleanup *cleanup)
{
	char	*outfile_path;
	char	*cmd;
	int		*pfd;
	int		outfile;
	int		i;

	outfile_path = data->argv[data->cmd_count + 2];
	cmd = data->argv[data->cmd_count + 1];
	pfd = data->pfd;
	i = data->index;
	outfile = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		cleanup_error("open outfile", cleanup, EXIT_FAILURE);
	close(pfd[2 * (i - 1) + 1]);
	exec_cmd(cmd, pfd[2 * (i - 1)], outfile, cleanup);
}

void	handle_middle_command(t_pipe_data *data, t_cleanup *cleanup)
{
	int		i;
	int		*pfd;
	char	**argv;

	i = data->index;
	pfd = data->pfd;
	argv = data->argv;
	close(pfd[2 * (i - 1) + 1]);
	exec_cmd(argv[i + 2], pfd[2 * (i - 1)], pfd[2 * i + 1], cleanup);
}

void	fork_and_execute(t_pipe_data *data, t_cleanup *cleanup)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		cleanup_error("fork", cleanup, EXIT_FAILURE);
	if (pid == 0)
	{
		if (data->index == 0)
			first_command(data, cleanup);
		else if (data->index == data->cmd_count - 1)
			last_command(data, cleanup);
		else
			handle_middle_command(data, cleanup);
	}
}
