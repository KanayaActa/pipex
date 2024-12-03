/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:04:47 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 09:45:12 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_cmd1(t_args *args, char **envp, int pipefd[2], pid_t *pid1)
{
	int		infile;

	*pid1 = fork();
	if (*pid1 < 0)
		print_error_and_exit(args->shell, "fork", EXIT_FAILURE);
	if (*pid1 == 0)
	{
		infile = open(args->infile, O_RDONLY);
		if (infile < 0)
			print_error_and_exit(args->shell, args->infile, EXIT_FAILURE);
		if (dup2(infile, STDIN_FILENO) == -1)
			print_error_and_exit(args->shell, "dup2 infile", EXIT_FAILURE);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			print_error_and_exit(args->shell, "dup2 pipefd[1]", EXIT_FAILURE);
		close(pipefd[0]);
		close(pipefd[1]);
		close(infile);
		execute_command(args->shell, args->cmd1, envp);
	}
}
