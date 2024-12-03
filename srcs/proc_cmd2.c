/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:45:13 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 09:45:21 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_cmd2(t_args *args, char **envp, int pipefd[2], pid_t *pid2)
{
	int		outfile;

	*pid2 = fork();
	if (*pid2 < 0)
		print_error_and_exit(args->shell, "fork", EXIT_FAILURE);
	if (*pid2 == 0)
	{
		outfile = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
			print_error_and_exit(args->shell, args->outfile, EXIT_FAILURE);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			print_error_and_exit(args->shell, "dup2 pipefd[0]", EXIT_FAILURE);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			print_error_and_exit(args->shell, "dup2 outfile", EXIT_FAILURE);
		close(pipefd[1]);
		close(pipefd[0]);
		close(outfile);
		execute_command(args->shell, args->cmd2, envp);
	}
}
