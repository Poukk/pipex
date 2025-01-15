/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:10:38 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 18:12:25 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	free(splited);
}
