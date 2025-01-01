#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
}

void	wait_for_children(int num_children)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_children)
	{
		wait(&status);
		i++;
	}
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
