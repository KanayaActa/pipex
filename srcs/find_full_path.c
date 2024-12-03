/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_full_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:17:45 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 10:26:16 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *create_full_path(const char *dir, const char *cmd)
{
	size_t len = strlen(dir) + 1 + strlen(cmd) + 1;
	char *full_path = malloc(len);
	if (!full_path)
		return NULL;
	snprintf(full_path, len, "%s/%s", dir, cmd);
	return full_path;
}

char *check_access(char *full_path)
{
	if (access(full_path, X_OK) == 0)
		return full_path;
	free(full_path);
	return NULL;
}

char *find_full_path(const char *cmd, const char *path_env)
{
	char *path_dup = strdup(path_env);
	if (!path_dup)
		return NULL;
	char *token = strtok(path_dup, ":");
	while (token)
	{
		char *full_path = create_full_path(token, cmd);
		if (!full_path)
		{
			free(path_dup);
			return NULL;
		}
		char *valid_path = check_access(full_path);
		if (valid_path)
		{
			free(path_dup);
			return valid_path;
		}
		token = strtok(NULL, ":");
	}
	free(path_dup);
	return NULL;
}
