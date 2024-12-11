#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int pfd[2];
	int status;
	pid_t pid1;
	pid_t pid2;

	if (argc != 5)
		usage_error();
	if (pipe(pfd) < 0)
		exit_error("pipe");
	pid1 = fork();
	if (pid1 < 0)
		exit_error("fork");
	if (pid1 == 0) {
        	close(pfd[0]);
        	write_end(argv[1], argv[2], pfd[1]);
	}
	pid2 = fork();
	if (pid2 < 0)
		exit_error("fork");
	if (pid2 == 0) {
		close(pfd[1]);
		read_end(argv[4], argv[3], pfd[0]);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if(WEXITSTATUS(status))
		exit(WEXITSTATUS(status));
	exit(EXIT_SUCCESS);
}
