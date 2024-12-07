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

int	_system(char *args[])
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
		execve("/bin/sh", args, NULL);
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

int	main(int argc, char *argv[])
{
	char	*args[4];

	if (argc != 2)
	{
		printf("Usage: ./pipex cmd\n");
		exit(1);
	}
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = argv[1];
	args[3] = NULL;
	_system(args);
}
