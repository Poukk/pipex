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

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipex.h"

extern char	**environ;

char	**argsgen(char *command)
{
	char	**args;

	args = malloc(4 * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = command;
	args[3] = NULL;
	return (args);
}
void	write_end(char *file_path, char *command, int pipe_end)
{
	int file;

	file = open(file_path, O_RDONLY);
	if (file < 0)
		exit_error("write_end - open");
	if (dup2(file, STDIN_FILENO) < 0)
		exit_error("write_end - dup2");
	if (close(file) < 0)
		exit_error("write_end - close");
	if (dup2(pipe_end, STDOUT_FILENO) < 0)
		exit_error("write_end - dup2");
	if (close(pipe_end) < 0)
		exit_error("write_end - close");
	execve("/bin/sh", argsgen(command), environ);
	exit_error("write_end - execve");
}

void	read_end(char *file_path, char *command, int pipe_end)
{
	int file;

	file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(file < 0)
		exit_error("read_end - open");
	if (dup2(pipe_end, STDIN_FILENO) < 0)
		exit_error("read_end - dup2");
	if (close(pipe_end) < 0)
		exit_error("read_end - close");
	if (dup2(file, STDOUT_FILENO) < 0)
		exit_error("read_end - dup2");
	if (close(file) < 0)
		exit_error("read_end - close");
	execve("/bin/sh", argsgen(command), environ);
	exit_error("read_end - execve");
}
