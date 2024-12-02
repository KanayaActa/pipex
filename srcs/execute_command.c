/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:39:41 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 11:55:16 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(const char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;
	char	*cmd_dup;
	int		i;

	cmd_dup = strdup(cmd);
	if (!cmd_dup)
		error_exit("strdup");
	i = 0;
	args = NULL;
	char *ptr = strtok(cmd_dup, " ");
	while (ptr)
	{
		args = realloc(args, sizeof(char *) * (i + 2));
		if (!args)
		{
			free(cmd_dup);
			error_exit("realloc");
		}
		args[i] = ptr;
		i++;
		ptr = strtok(NULL, " ");
	}
	if (args)
		args[i] = NULL;
	cmd_path = get_command_path(args[0], envp);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		free(args);
		free(cmd_dup);
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror("execve");
	free(cmd_path);
	free(args);
	free(cmd_dup);
	exit(EXIT_FAILURE);
}
