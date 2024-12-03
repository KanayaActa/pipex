/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:39:41 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 12:33:17 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_eacces(const char *shell, const char *cmd)
{
	if (errno == EACCES)
		print_error_and_exit(shell, cmd, 126);
}

static void	handle_command_not_found(char **args, const char *cmd)
{
	char	*buf;
	size_t	size;

	size = strlen(cmd) + strlen(": command not found\n") + 1;
	buf = __builtin_alloca(size);
	strlcpy(buf, cmd, size);
	strlcat(buf, ": command not found\n", size);
	perror(buf);
	free(args);
	exit(127);
}

static void	open_command_path(const char *shell, const char *cmd_path)
{
	int	fd;

	fd = open(cmd_path, O_WRONLY);
	if (fd == -1 && errno == EISDIR)
		print_error_and_exit(shell, cmd_path, 126);
	close(fd);
}

void	execute_command(const char *shell, const char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = parse_command(shell, cmd);
	if (!args)
		print_error_and_exit(shell, "parse_command", EXIT_FAILURE);
	cmd_path = get_command_path(args[0], envp);
	check_eacces(shell, args[0]);
	if (!cmd_path)
		handle_command_not_found(args, args[0]);
	open_command_path(shell, cmd_path);
	execve(cmd_path, args, envp);
	print_error_and_exit(shell, "execve", EXIT_FAILURE);
	free(cmd_path);
	free(args);
	exit(EXIT_FAILURE);
}
