/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:53:03 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/01 17:53:10 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

# include <errno.h> 
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

# define HELP_MESSAGE "Usage: ./pipex file1 cmd1 cmd2 file2\n"

typedef struct s_args
{
	const char	*infile;
	const char	*cmd1;
	const char	*cmd2;
	const char	*outfile;
}	t_args;

void	is_valid_args(int argc, char **argv);
void	option_help(int fd, const char *op);
void	create_pipe(int **pipefd);
void	proc_cmd(pid_t pid);

#endif
