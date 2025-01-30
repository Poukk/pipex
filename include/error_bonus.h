/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:45:03 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 17:45:09 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

typedef struct s_cleanup
{
	void	*ptr;
	void	(*cleanup_fn)(void*);
}	t_cleanup;

void	cleanup_error(char *error_msg, t_cleanup *cleanup_data, int status);
void	usage_error(void);
void	reg_cleanup(t_cleanup *to_clean, void *ptr, void (*cleanup_fn)(void*));
void	exit_error(char *error_msg);

#endif
