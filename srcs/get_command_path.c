/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:42:00 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 10:57:17 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(const char *cmd, char **envp)
{
	char	*path_env = NULL;
	char	*path_dup = NULL;
	char	*token = NULL;
	char	*full_path = NULL;
	size_t	len;

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return strdup(cmd);
		else
			return NULL;
	}

	for (int i = 0; envp[i]; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
	}

	if (!path_env)
		return NULL;

	path_dup = strdup(path_env);
	if (!path_dup)
		return NULL;

	token = strtok(path_dup, ":");
	while (token)
	{
		len = strlen(token) + 1 + strlen(cmd) + 1;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_dup);
			return NULL;
		}
		snprintf(full_path, len, "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_dup);
			return full_path;
		}
		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_dup);
	return NULL;
}
