/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:39:41 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 10:39:54 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void check_eacces(const char *cmd)
{
	if (errno == EACCES)
	{
		perror(cmd);
		exit(126);
	}
}

void handle_command_not_found(char **args, const char *cmd)
{
	fprintf(stderr, "pipex: %s: command not found\n", cmd);
	free(args);
	exit(127);
}

void open_command_path(const char *cmd_path)
{
	int fd = open(cmd_path, O_WRONLY);
	if (fd == -1)
	{
		if (errno == EISDIR)
		{
			perror(cmd_path);
			exit(126);
		}
	}
	close(fd);
}

void execute_command(const char *shell, const char *cmd, char **envp)
{
	char **args = parse_command(cmd);
	if (!args)
		print_error_and_exit(shell, "parse_command", EXIT_FAILURE);
	char *cmd_path = get_command_path(args[0], envp);
	check_eacces(args[0]);
	if (!cmd_path)
		handle_command_not_found(args, args[0]);
	open_command_path(cmd_path);
	execve(cmd_path, args, envp);
	perror("execve");
	free(cmd_path);
	free(args);
	exit(EXIT_FAILURE);
}