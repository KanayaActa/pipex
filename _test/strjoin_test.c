// main.c
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"

// 関数プロトタイプの宣言
char *strjoin(const char *s1, const char *s2);
void print_error_and_exit(const char *shell, const char *cmd, int status);

int main(void) {
    const char *shell_name = "pipex"; // シェルやプログラムの名前
    const char *command = "ks";        // 存在しないコマンド
    int status = 127;                  // コマンドが見つからない場合の終了ステータス

    // 子プロセスを生成
    pid_t pid = fork();
    if (pid < 0) {
        // forkが失敗した場合
        print_error_and_exit(shell_name, "fork", EXIT_FAILURE);
    }

    if (pid == 0) {
        // 子プロセス: 存在しないコマンドを実行しようとする
        char *args[] = {(char *)command, NULL};
        execvp(command, args);

        // execvpが失敗した場合
        print_error_and_exit(shell_name, command, status);
    } else {
        // 親プロセス: 子プロセスの終了を待つ
        int wstatus;
        if (waitpid(pid, &wstatus, 0) == -1) {
            // waitpidが失敗した場合
            print_error_and_exit(shell_name, "waitpid", EXIT_FAILURE);
        }

        if (WIFEXITED(wstatus)) {
            // 子プロセスが正常に終了した場合、親プロセスも同じステータスで終了
            exit(WEXITSTATUS(wstatus));
        } else if (WIFSIGNALED(wstatus)) {
            // 子プロセスがシグナルで終了した場合
            fprintf(stderr, "%s: Child process terminated by signal %d\n", shell_name, WTERMSIG(wstatus));
            exit(128 + WTERMSIG(wstatus));
        } else {
            // その他の異常な終了状態
            exit(EXIT_FAILURE);
        }
    }

    return 0; // 実際には到達しません
}
