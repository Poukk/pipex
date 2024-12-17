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

void	write_end(char *file_path, char *command, int pipe_end)
{
	char **splited_command;
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
	splited_command = ft_split(command, ' ');
	execve(splited_command[0], (splited_command + 1), environ);
	free_split(splited_command);
	exit_error("write_end - execve");
}

void	read_end(char *file_path, char *command, int pipe_end)
{
	char **splited_command;
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
	splited_command = ft_split(command, ' ');
	execve(splited_command[0], (splited_command + 1), environ);
	free_split(splited_command);
	exit_error("read_end - execve");
}
