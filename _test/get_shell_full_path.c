/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_full_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:20:17 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 10:22:40 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

const char *get_shell_proc(void);
/* 前述の関数 get_ppid_from_stat と get_parent_comm をここに含める */

/**
 * シェルのフルパスを取得する関数
 * 
 * @param comm 親プロセスのコマンド名
 * @return シェルのフルパスへのポインタ（mallocで割り当てられており、呼び出し元でfreeする必要があります）、失敗時はNULL
 */
const char *get_shell_full_path(const char *comm) {
    // 環境変数 PATH を取得するために /proc/self/environ を読み取る
    // 簡易的な実装として、特定のディレクトリを検索する
    // ここでは、代表的なシェルディレクトリを順にチェックします

    const char *paths[] = {
        "/bin/",
        "/usr/bin/",
        "/usr/local/bin/",
        NULL
    };

    for (int i = 0; paths[i] != NULL; i++) {
        size_t dir_len = strlen(paths[i]);
        size_t cmd_len = strlen(comm);
        size_t full_len = dir_len + cmd_len + 1;

        char *full_path = (char *)malloc(full_len);
        if (full_path == NULL) {
            perror("malloc");
            return NULL;
        }

        // パスを構築
        for (size_t j = 0; j < dir_len; j++) {
            full_path[j] = paths[i][j];
        }
        for (size_t j = 0; j < cmd_len; j++) {
            full_path[dir_len + j] = comm[j];
        }
        full_path[dir_len + cmd_len] = '\0';

        // ファイルが実行可能かチェック
        if (access(full_path, X_OK) == 0) {
            return full_path; // 呼び出し元でfreeする必要あり
        }

        free(full_path);
    }

    // 見つからなかった場合
    return NULL;
}

int main() {
    const char *shell = get_shell_proc();
    if (shell != NULL) {
        // シェルのフルパスを取得
        const char *shell_full_path = get_shell_full_path(shell);
        if (shell_full_path != NULL) {
            // シェルのフルパスを標準出力に表示
            const char *message = "現在のシェルのフルパス: ";
            size_t msg_len = 19; // strlen("現在のシェルのフルパス: ")
            write(STDOUT_FILENO, message, msg_len);

            size_t shell_len = 0;
            while (shell_full_path[shell_len] != '\0') {
                shell_len++;
            }
            write(STDOUT_FILENO, shell_full_path, shell_len);
            write(STDOUT_FILENO, "\n", 1);

            // メモリを解放
            free((void *)shell_full_path);
        } else {
            const char *msg = "シェルのフルパスを取得できませんでした。\n";
            write(STDERR_FILENO, msg, strlen(msg));
        }

        // シェル名のメモリを解放
        free((void *)shell);
    } else {
        // エラーメッセージは get_shell_proc 内で表示済み
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
