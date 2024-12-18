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

void	write_end(char *file_path, char *command, int pipe_end);
void	read_end(char *file_path, char *command, int pipe_end);


char	**ft_split(char const *s, char c);
void	free_split(char **splited);
#endif
