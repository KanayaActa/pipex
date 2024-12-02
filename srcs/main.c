/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:10:58 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 10:52:23 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	t_args	args;

	is_valid_args(argc, argv);
	init_args(&args, argv);
	create_pipe(&pipefd);
	proc_cmd1(&args, envp, pipefd, &pid1);
	proc_cmd2(&args, envp, pipefd, &pid2);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	(void)args;
	(void)envp;
	(void)argv;
	return (0);
}
