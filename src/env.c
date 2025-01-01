#include "pipex.h"
#include <stdlib.h>

extern char	**environ;

char	*_getenv(const char *name)
{
	int		name_len;
	char	**env_copy;

	name_len = ft_strlen(name);
	env_copy = environ;
	while (*env_copy != NULL)
	{
		if (ft_strncmp(name, *env_copy, name_len) == 0)
			return (*env_copy + name_len + 1);
		env_copy++;
	}
	return (NULL);
}

char	*find_path(char *cmd)
{
	char	**splited_path;
	char	*joined_cmd;
	char	*tmp_path;
	char	*env_path;

	env_path = _getenv("PATH");
	splited_path = ft_split(env_path, ':');
	if (!splited_path)
		return (NULL);
	while (*splited_path != NULL)
	{
		tmp_path = ft_strjoin(*splited_path, "/");
		joined_cmd = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(joined_cmd, F_OK) == 0)
		{
			free_split(splited_path);
			return (joined_cmd);
		}
		free(joined_cmd);
		splited_path++;
	}
	free_split(splited_path);
	return (NULL);
}
