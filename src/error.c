/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:52:00 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 17:54:56 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include <stdio.h>

void	usage_error(void)
{
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	exit(EXIT_FAILURE);
}

void	exit_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void	exit_wcode(char *error_msg, int exit_code)
{
	ft_putstr_fd(error_msg, 2);
	exit(exit_code);
}
