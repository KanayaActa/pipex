/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:42:00 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 11:33:56 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*has_slash(const char *cmd)
{
	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		else
			return (NULL);
	}
	return (NULL);
}

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_command_path(const char *cmd, char **envp)
{
	char	*cmd_path;
	char	*path_env;

	cmd_path = has_slash(cmd);
	if (cmd_path)
		return (cmd_path);
	path_env = get_path_env(envp);
	if (!path_env)
		return (NULL);
	return (find_full_path(cmd, path_env));
}
