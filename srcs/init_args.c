/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:02:37 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/01 19:53:23 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_args(t_args *args, char **argv)
{
	args->infile = argv[1];
	args->cmd1 = argv[2];
	args->cmd2 = argv[3];
	args->outfile = argv[4];
}
