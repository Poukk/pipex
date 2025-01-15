/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:28:04 by alexanfe          #+#    #+#             */
/*   Updated: 2025/01/15 17:28:07 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init(t_pipe_data *data, t_cleanup *cleanup, int argc, char *argv[])
{
	if (argc < 5)
		usage_error();
	data->cmd_count = argc - 3;
	data->pfd = malloc((argc - 4) * 2 * sizeof(int));
	data->argv = argv;
	data->index = 0;
	if (!data->pfd)
		cleanup_error("malloc", NULL);
	reg_cleanup(cleanup, data->pfd, free_pipes);
	setup_pipes(data->pfd, argc - 4);
}

int	main(int argc, char *argv[])
{
	t_pipe_data	data;
	t_cleanup	cleanup_data;
	int			last_status;

	init(&data, &cleanup_data, argc, argv);
	while (data.index < data.cmd_count)
	{
		fork_and_execute(&data, &cleanup_data);
		if (data.index > 0)
		{
			close(data.pfd[2 * (data.index - 1)]);
			close(data.pfd[2 * (data.index - 1) + 1]);
		}
		data.index++;
	}
	close_pipes(data.pfd, argc - 4);
	last_status = wait_for_children(data.cmd_count);
	free(data.pfd);
	return (last_status);
}
