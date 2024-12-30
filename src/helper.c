/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:30:30 by alexanfe          #+#    #+#             */
/*   Updated: 2024/12/12 06:31:04 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	src_len;
	unsigned int	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size > 0)
	{
		i = 0;
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
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
	while (i < num_children)
	{
		wait(&status);
		i++;
	}
}
