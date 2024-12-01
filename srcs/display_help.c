/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:25:27 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/01 19:57:34 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_help(int fd, const char *op)
{
	if (fd == STDERR_FILENO || !op)
		ft_putstr_fd(HELP_MESSAGE, fd);
	else if (!ft_strcmp(op, "--help") || !ft_strcmp(op, "-h"))
	{
		ft_putstr_fd(HELP_MESSAGE, fd);
		if (fd == STDOUT_FILENO)
			exit(EXIT_SUCCESS);
	}
}
