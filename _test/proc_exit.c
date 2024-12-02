/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:23:45 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 13:37:02 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int	main(void)
{
	int		fd;
	pid_t	pid;
	int		status;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	if (pid < 0)
	{
		exit(1);
	}
	if (pid == 0)
	{
		exit(42);
	}
	if (waitpid(pid, &status, 0) == -1)
		;
	if ((status & 0x7F) == 0)
		exit_status = (status >> 8) & 0xFF;
	exit (exit_status);
}
