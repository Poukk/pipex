#ifndef ERROR_H
# define ERROR_H

typedef struct s_cleanup
{
	void	*ptr;
	void	(*cleanup_fn)(void*);
}	t_cleanup;

void	cleanup_error(char *error_msg, t_cleanup *cleanup_data);
void	usage_error(void);
void	reg_cleanup(t_cleanup *to_clean, void *ptr, void (*cleanup_fn)(void*));
void	exit_error(char *error_msg);

#endif