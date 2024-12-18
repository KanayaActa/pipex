/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:10:58 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 12:37:46 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;
	t_args	args;

	is_valid_args(argc, argv);
	init_args(&args, argv);
	create_pipe(args.shell, &pipefd);
	proc_cmd1(&args, envp, pipefd, &pid1);
	proc_cmd2(&args, envp, pipefd, &pid2);
	close(pipefd[0]);
	close(pipefd[1]);
	if (waitpid(pid1, &status, 0) == -1)
		print_error_and_exit(args.shell, "waitpid", EXIT_FAILURE);
	if (wifexited(status))
		status = wexitstatus(status);
	if (waitpid(pid2, &status, 0) == -1)
		print_error_and_exit(args.shell, "waitpid", EXIT_FAILURE);
	if (wifexited(status))
		status = wexitstatus(status);
	exit(status);
}
