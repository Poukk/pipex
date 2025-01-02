#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "pipex.h"
#include "error.h"

extern char	**environ;

static void    execute_command(char *cmd, int in_fd, int out_fd, t_cleanup *cleanup_data)
{
	char    **splited_cmd;
	char    *cmd_path;

	if (dup2(in_fd, STDIN_FILENO) == -1 || dup2(out_fd, STDOUT_FILENO) == -1)
		cleanup_error("dup2", cleanup_data);
	close(in_fd);
	close(out_fd);
	splited_cmd = ft_split(cmd, ' ');
	if (!splited_cmd)
		cleanup_error("malloc", cleanup_data);
	cmd_path = find_path(splited_cmd[0]);
	if (!cmd_path)
	{
		free_split(splited_cmd);
		cleanup_error("command not found", cleanup_data);
	}
	free(splited_cmd[0]);
	splited_cmd[0] = cmd_path;
	execve(cmd_path, splited_cmd, environ);
	free_split(splited_cmd);
	free(cmd_path);
	cleanup_error("execve", cleanup_data);
}

static void    first_command(char *infile_path, char *command, int *pfd, t_cleanup *cleanup_data)
{
	int    infile;

	infile = open(infile_path, O_RDONLY);
	if (infile < 0)
		cleanup_error("open infile", cleanup_data);
	close(pfd[0]);
	execute_command(command, infile, pfd[1], cleanup_data);
}

static void    last_command(char *outfile_path, char *command, int *pfd, int index, t_cleanup *cleanup_data)
{
	int    outfile;

	outfile = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		cleanup_error("open outfile", cleanup_data);
	close(pfd[2 * (index - 1) + 1]);
	execute_command(command, pfd[2 * (index - 1)], outfile, cleanup_data);
}

void    fork_and_execute(char *argv[], int *pfd, int i, int argc, t_cleanup *cleanup_data)
{
	pid_t    pid;

	pid = fork();
	if (pid < 0)
		cleanup_error("fork", cleanup_data);
	if (pid == 0)
	{
		if (i == 0)
			first_command(argv[1], argv[2], pfd, cleanup_data);
		else if (i == argc - 4)
			last_command(argv[argc - 1], argv[argc - 2], pfd, i, cleanup_data);
		else
		{
			close(pfd[2 * (i - 1) + 1]);
			execute_command(argv[i + 2], pfd[2 * (i - 1)], pfd[2 * i + 1], cleanup_data);
		}
	}
}
