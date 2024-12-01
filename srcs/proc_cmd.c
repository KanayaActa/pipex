/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:04:47 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/01 19:48:25 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_cmd(t_args args, char **envp, int *pipefd, pid_t pid)
{
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		int infile = open(argv[1], O_RDONLY);
		if (infile < 0) {
			perror("open infile");
			exit(EXIT_FAILURE);
		}

		dup2(infile, STDIN_FILENO);      // file1を標準入力にリダイレクト
		dup2(pipefd[1], STDOUT_FILENO);   // パイプの書き込み側を標準出力にリダイレクト
		close(pipefd[0]);                 // パイプの読み取り側を閉じる
		close(pipefd[1]);
		close(infile);

		char *cmd1[] = {"/bin/sh", "-c", argv[2], NULL};
		execve(cmd1[0], cmd1, envp);      // cmd1の実行
		perror("execve cmd1 failed");
		exit(EXIT_FAILURE);
	}
}
