/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:05:13 by alexanfe          #+#    #+#             */
/*   Updated: 2024/12/11 02:05:15 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

extern char	**environ;

void	execute_command(char *cmd, int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) == -1 || dup2(out_fd, STDOUT_FILENO) == -1)
		exit_error("dup2");
	close(in_fd);
	close(out_fd);
	execlp(cmd, cmd, (char *) NULL);
	exit_error("execlp");
}

void	fork_and_execute(char *argv[], int *pfd, int i, int argc)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_error("fork");
	if (pid == 0)
	{
		if (i == 0)
		{
			int infile = open(argv[1], O_RDONLY);
			if (infile < 0)
				exit_error("open infile");
			close(pfd[0]);
			execute_command(argv[2], infile, pfd[1]);
        	}
		else if (i == argc - 4)
		{
			int outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (outfile < 0)
				exit_error("open outfile");
			close(pfd[2 * (i - 1) + 1]);
			execute_command(argv[argc - 2], pfd[2 * (i - 1)], outfile);
        	}
		else
		{
			close(pfd[2 * (i - 1) + 1]);
			execute_command(argv[i + 2], pfd[2 * (i - 1)], pfd[2 * i + 1]);
		}
	}
}
