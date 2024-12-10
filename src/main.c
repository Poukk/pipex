/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:46:01 by alexanfe          #+#    #+#             */
/*   Updated: 2024/11/26 21:46:07 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
/*
int	_system(char *command)
{
	int		status;
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	else if (child_pid == 0)
	{
		execve("/bin/sh", argsgen(command), environ);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("waitpid failed");
			return (-1);
		}
		return (status);
	}
}
*/

void	usage_error(void)
{
	printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
	exit(EXIT_FAILURE);
}

// TODO: change perror to error functions
int	write_end(char *file_path, char *command, int pipe_end)
{
	int file;

	file = open(file_path, O_RDONLY);
	if(file < 0)
	{
		perror("open");
		return(-1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	if (dup2(pipe_end, STDOUT_FILENO) == -1)
		perror("dup2 1"); //change this
	if (close(pipe_end) == -1)
		perror("close 2"); //change this
	execve("/bin/sh", argsgen(command), environ);
	perror("execve - write_end");
	exit(EXIT_FAILURE);
}

int	read_end(char *file_path, char *command, int pipe_end)
{
	int file;

	file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(file < 0)
	{
		perror("open");
		return(-1);
	}
	if (dup2(pipe_end, STDIN_FILENO) == -1)
		perror("dup2 1");
	if (close(pipe_end) == -1)
		perror("close 1");
	if (dup2(file, STDOUT_FILENO) == -1)
		perror("dup2 2");
	if (close(file) == -1)
		perror("close 2");
	execve("/bin/sh", argsgen(command), environ);
	perror("execve - read_end");
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int pfd[2];
	if (argc != 5)
		usage_error();
	if (pipe(pfd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pfd[0]);
        write_end(argv[1], argv[2], pfd[1]);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pfd[1]);
        read_end(argv[4], argv[3], pfd[0]);
    }

    // Parent process
    close(pfd[0]); // Close both ends of the pipe
    close(pfd[1]);

    waitpid(pid1, NULL, 0); // Wait for first child
    waitpid(pid2, NULL, 0); // Wait for second child
	exit(EXIT_SUCCESS);
}
