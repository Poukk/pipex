/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:24:14 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 18:24:17 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "error.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**argv;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

void	exec_cmd(char *cmd, int in_fd, int out_fd);

char	*_getenv(const char *name);
char	**get_path(void);
char	*find_path(char *cmd);

void	free_split(char **splited);

void	execute_first_cmd(t_pipex *pipex);
void	execute_second_cmd(t_pipex *pipex);
#endif
