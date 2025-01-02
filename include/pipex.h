/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:46:16 by alexanfe          #+#    #+#             */
/*   Updated: 2024/11/26 21:46:22 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "libft.h"
# include "error.h"

/* env */
char	*_getenv(const char *name);
char	*find_path(char *cmd);

/* exec */
void    fork_and_execute(char *argv[], int *pfd, int i, int argc, t_cleanup *cleanup_data);

/* helper */
int     wait_for_children(int num_children);
void	free_split(char **splited);
void	setup_pipes(int *pfd, int num_pipes);
void	close_pipes(int *pfd, int num_pipes);
void    free_pipes(void *ptr);

#endif
