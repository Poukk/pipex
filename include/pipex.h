/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 22:07:54 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/02 22:07:58 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "error.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_pipe_data
{
	int		*pfd;
	int		index;
	int		cmd_count;
	char	**argv;
}	t_pipe_data;

/* env */
char	*_getenv(const char *name);
char	**get_path(void);
char	*find_path(char *cmd);

/* exec */
void	fork_and_execute(t_pipe_data *data, t_cleanup *cleanup);

/* helper */
int		wait_for_children(int num_children);
void	free_split(char **splited);
void	setup_pipes(int *pfd, int num_pipes);
void	close_pipes(int *pfd, int num_pipes);
void	free_pipes(void *ptr);

#endif
