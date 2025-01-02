#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int    main(int argc, char *argv[])
{
    int            num_pipes;
    int            *pfd;
    int            i;
    int            last_status;
    t_cleanup    cleanup_data = {NULL, NULL};

    if (argc < 5)
        usage_error();
    num_pipes = argc - 4;
    pfd = malloc(num_pipes * 2 * sizeof(int));
    if (!pfd)
        cleanup_error("malloc", NULL);
    register_cleanup(&cleanup_data, pfd, free_pipes);
    
    setup_pipes(pfd, num_pipes);
    i = 0;
    while (i < argc - 3)
    {
        fork_and_execute(argv, pfd, i, argc, &cleanup_data);
        if (i > 0)
        {
            close(pfd[2 * (i - 1)]);
            close(pfd[2 * (i - 1) + 1]);
        }
        i++;
    }
    close_pipes(pfd, num_pipes);
    last_status = wait_for_children(argc - 3);
    free(pfd);
    return (last_status);
}
