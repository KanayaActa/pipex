/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:52:40 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/03 12:27:19 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error_and_exit(const char *shell, const char *cmd, int status)
{
	char		*buf;
	size_t		size;

	size = strlen(shell) + strlen(": ") + strlen(cmd) + 1;
	buf = __builtin_alloca(size);
	ft_strlcpy(buf, shell, size);
	ft_strlcat(buf, ": ", size);
	ft_strlcat(buf, cmd, size);
	perror(buf);
	exit(status);
}
