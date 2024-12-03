/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_full_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:17:45 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 11:34:19 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*create_full_path(const char *dir, const char *cmd)
{
	char	*full_path;
	size_t	dir_len;
	size_t	cmd_len;
	size_t	len;

	dir_len = strlen(dir);
	cmd_len = strlen(cmd);
	len = dir_len + 1 + cmd_len + 1;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	memcpy(full_path, dir, dir_len);
	full_path[dir_len] = '/';
	strcpy(full_path + dir_len + 1, cmd);
	return (full_path);
}

static char	*check_access(char *full_path)
{
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_full_path(const char *cmd, const char *path_env)
{
	char	*path_dup;
	char	*token;
	char	*full_path;
	char	*valid_path;

	path_dup = strdup(path_env);
	if (!path_dup)
		return (NULL);
	token = strtok(path_dup, ":");
	while (token)
	{
		full_path = create_full_path(token, cmd);
		if (!full_path)
			return (free(path_dup), NULL);
		valid_path = check_access(full_path);
		if (valid_path)
			return (free(path_dup), valid_path);
		token = strtok(NULL, ":");
	}
	return (free(path_dup), NULL);
}
