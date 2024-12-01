/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:07:55 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/01 15:36:16 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	is_valid_args(int argc, char **argv)
{
	if (argc == 2)
		option_help(STDOUT_FILENO, argv[1]);
	if (argc != 5)
	{
		errno = EINVAL;
		perror(NULL);
		option_help(STDERR_FILENO, NULL);
		exit(EXIT_FAILURE);
	}
}
