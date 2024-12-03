/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:52:00 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 12:38:16 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(const char *shell, int (*pipefd)[2])
{
	if (pipe(*pipefd) == -1)
		print_error_and_exit(shell, "pipe", EXIT_FAILURE);
}
