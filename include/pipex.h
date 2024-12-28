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

void	usage_error(void);
void	exit_error(char *error_msg);

void	fork_and_execute(char *argv[], int *pfd, int i, int argc);


char	**ft_split(char const *s, char c);
void	free_split(char **splited);
#endif
