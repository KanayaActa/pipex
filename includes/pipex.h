/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 12:53:03 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 10:57:11 by miwasa           ###   ########.fr       */
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
# include <fcntl.h>

# include <string.h>

# define HELP_MESSAGE "Usage: ./pipex file1 cmd1 cmd2 file2\n"

typedef struct s_args
{
	const char	*shell;
	const char	*infile;
	const char	*cmd1;
	const char	*cmd2;
	const char	*outfile;
}	t_args;

void		is_valid_args(int argc, char **argv);
void		display_help(int fd, const char *op);
void		init_args(t_args *args, char **argv);
char		*get_shell_proc(void);
void		create_pipe(int (*pipefd)[2]);
void		proc_cmd1(t_args *args, char **envp, int pipefd[2], pid_t *pid1);
void		proc_cmd2(t_args *args, char **envp, int pipefd[2], pid_t *pid2);
void		error_exit(const char *msg);
void		execute_command(const char *cmd, char **envp);
char		*get_command_path(const char *cmd, char **envp);

#endif
