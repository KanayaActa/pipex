/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:52:57 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 12:36:09 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_tokens(const char *cmd)
{
	int	count;
	int	in_token;

	count = 0;
	in_token = 0;
	while (*cmd)
	{
		if (*cmd != ' ' && !in_token)
		{
			in_token = 1;
			count++;
		}
		else if (*cmd == ' ')
			in_token = 0;
		cmd++;
	}
	return (count);
}

static char	**allocate_args(int count)
{
	char	**args;

	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
	{
		perror("malloc");
		return (NULL);
	}
	return (args);
}

static char	**fill_args(char *cmd_dup, char **args)
{
	int		i;
	char	*start;

	i = 0;
	start = NULL;
	while (*cmd_dup)
	{
		if (*cmd_dup != ' ' && start == NULL)
			start = cmd_dup;
		if ((*cmd_dup == ' ' || *(cmd_dup + 1) == '\0') && start != NULL)
		{
			if (*cmd_dup == ' ')
				*cmd_dup = '\0';
			args[i++] = start;
			start = NULL;
		}
		cmd_dup++;
	}
	args[i] = NULL;
	return (args);
}

char	**parse_command(const char *shell, const char *cmd)
{
	char	*cmd_dup;
	int		token_count;
	char	**args;

	cmd_dup = strdup(cmd);
	if (!cmd_dup)
		print_error_and_exit(shell, "strdup", EXIT_FAILURE);
	token_count = count_tokens(cmd_dup);
	if (token_count == 0)
	{
		free(cmd_dup);
		return (NULL);
	}
	args = allocate_args(token_count);
	if (!args)
	{
		free(cmd_dup);
		print_error_and_exit(shell, "allocate", EXIT_FAILURE);
	}
	args = fill_args(cmd_dup, args);
	return (args);
}
