#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	free(splited);
}

int	wait_for_children(int num_processes)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	while (num_processes > 0)
	{
		pid = wait(&status);
		if (pid == -1)
			exit_error("wait");
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		num_processes--;
	}
	return (last_status);
}

void	setup_pipes(int *pfd, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pfd + 2 * i) < 0)
			exit_error("pipe");
		i++;
	}
}

void	close_pipes(int *pfd, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pfd[2 * i]);
		close(pfd[2 * i + 1]);
		i++;
	}
}

void	free_pipes(void *ptr)
{
	free(ptr);
}
