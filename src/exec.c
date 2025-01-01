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
#include <stdlib.h>
#include "pipex.h"

extern char	**environ;

static void execute_command(char *cmd, int in_fd, int out_fd)
{
    char **splited_cmd;
    char *cmd_path;

    if (dup2(in_fd, STDIN_FILENO) == -1 || dup2(out_fd, STDOUT_FILENO) == -1)
        exit_error("dup2");
    close(in_fd);
    close(out_fd);
    splited_cmd = ft_split(cmd, ' ');
    if (!splited_cmd)
        exit_error("malloc"); 
    cmd_path = find_path(splited_cmd[0]);
    if (!cmd_path)
    {
        free_split(splited_cmd);
        exit_error("command not found");
    }
    free(splited_cmd[0]);
    splited_cmd[0] = cmd_path;
    execve(cmd_path, splited_cmd, environ);    
    free_split(splited_cmd);
    exit_error("execve");
}

static void	first_command(char *infile_path, char *command, int *pfd)
{
	int	infile;

	infile = open(infile_path, O_RDONLY);
	if (infile < 0)
		exit_error("open infile");
	close(pfd[0]);
	execute_command(command, infile, pfd[1]);
}

static void	last_command(char *outfile_path, char *command, int *pfd, int index)
{
	int	outfile;

	outfile = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		exit_error("open outfile");
	close(pfd[2 * (index - 1) + 1]);
	execute_command(command, pfd[2 * (index - 1)], outfile);
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
			first_command(argv[1], argv[2], pfd);
		else if (i == argc - 4)
			last_command(argv[argc - 1], argv[argc - 2], pfd, i);
		else
		{
			close(pfd[2 * (i - 1) + 1]);
			execute_command(argv[i + 2], pfd[2 * (i - 1)], pfd[2 * i + 1]);
		}
	}
}
