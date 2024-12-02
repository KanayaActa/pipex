/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:45:13 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 10:59:01 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_cmd2(t_args *args, char **envp, int pipefd[2], pid_t *pid2)
{
	int		outfile;

	*pid2 = fork();
	if (*pid2 < 0)
		error_exit("fork");
	if (*pid2 == 0)
	{
		outfile = open(args->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
		{
			perror(args->outfile);
			exit(1);
		}
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			error_exit("dup2 pipefd[0]");
		if (dup2(outfile, STDOUT_FILENO) == -1)
			error_exit("dup2 outfile");
		close(pipefd[1]);
		close(pipefd[0]);
		close(outfile);
		execute_command(args->cmd2, envp);
	}
}
