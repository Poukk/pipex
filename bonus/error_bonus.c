/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:43:58 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 17:44:06 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error_bonus.h"
#include <stdio.h>
#include <stdlib.h>

void	cleanup_error(char *error_msg, t_cleanup *cleanup_data, int status)
{
	if (cleanup_data && cleanup_data->ptr && cleanup_data->cleanup_fn)
		cleanup_data->cleanup_fn(cleanup_data->ptr);
	perror(error_msg);
	exit(status);
}

void	usage_error(void)
{
	ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
	exit(EXIT_FAILURE);
}

void	reg_cleanup(t_cleanup *to_clean, void *ptr, void (*cleanup_fn)(void*))
{
	to_clean->ptr = ptr;
	to_clean->cleanup_fn = cleanup_fn;
}

void	exit_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}
