/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:10:58 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/01 17:56:34 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	is_valid_args(argc, argv);
	init_args(argv);
	create_pipe(pipefd);
	proc_cmd(pid1);
	proc_cmd(pid2);
	close(pipefd[0]);
	clode(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	(void)envp;
	(void)argv;
	return (0);
}
