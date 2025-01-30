/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:06:14 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/30 15:06:15 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	duplicate_std(int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) < 0)
		exit_error("dup2 error");
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		exit_error("dup2 error");
	close(in_fd);
	close(out_fd);
}

int	is_exec(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}
