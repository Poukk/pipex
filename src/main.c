/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:04:46 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 18:05:02 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	t_pipex	pipex;
	int		status;

	if (argc != 5)
		usage_error();
	pipex.argv = argv;
	if (pipe(pipex.pipe_fd) < 0)
		exit_error("Pipe error");
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		exit_error("Fork error");
	if (pipex.pid1 == 0)
		execute_first_cmd(&pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		exit_error("Fork error");
	if (pipex.pid2 == 0)
		execute_second_cmd(&pipex);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(pipex.pid1, &status, 0);
	waitpid(pipex.pid2, &status, 0);
	return (WEXITSTATUS(status));
}
