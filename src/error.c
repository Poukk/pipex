#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void    cleanup_error(char *error_msg, t_cleanup *cleanup_data)
{
    if (cleanup_data && cleanup_data->ptr && cleanup_data->cleanup_fn)
        cleanup_data->cleanup_fn(cleanup_data->ptr);
    perror(error_msg);
    exit(EXIT_FAILURE);
}

void    usage_error(void)
{
    printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
    exit(EXIT_FAILURE);
}

void    register_cleanup(t_cleanup *cleanup_data, void *ptr, void (*cleanup_fn)(void*))
{
    cleanup_data->ptr = ptr;
    cleanup_data->cleanup_fn = cleanup_fn;
}

void	exit_error(char *error_msg)
{

	perror(error_msg);

	exit(EXIT_FAILURE);

}
