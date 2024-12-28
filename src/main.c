#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

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

void	wait_for_children(int num_children)
{
	int	status;
	int	i;

	i = 0;
	while(i < num_children)
	{
		wait(&status);
		i++;
	}
}

int main(int argc, char *argv[])
{
	int	num_pipes;
	int	*pfd;
	int	i;

	if (argc < 5)
		usage_error();
	num_pipes = argc - 4;
	pfd = malloc(num_pipes * 2 * sizeof(int));
	if (!pfd)
        	exit_error("malloc");
	setup_pipes(pfd, num_pipes);
	i = 0;
	while (i< argc -3)
	{
        	fork_and_execute(argv, pfd, i, argc);
		if (i > 0)
		{
			close(pfd[2 * (i - 1)]);
			close(pfd[2 * (i - 1) + 1]);
		}
		i++;
	}
	close_pipes(pfd, num_pipes);
	wait_for_children(argc - 3);
	free(pfd);
	return 0;
}
