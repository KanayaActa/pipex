/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:52:00 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 10:56:40 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(int (*pipefd)[2])
{
	if (pipe(*pipefd) == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
}
