/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:48:02 by miwasa            #+#    #+#             */
/*   Updated: 2024/12/02 09:48:28 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/**
 * エラーメッセージを表示してプログラムを終了する関数
 */
void error_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

/**
 * /proc/self/stat から ppid を取得する関数
 * 
 * @param ppid ポインタを通じて ppid を返す
 * @return 0 成功, -1 失敗
 */
int get_ppid_from_stat(pid_t *ppid) {
    int fd;
    ssize_t bytes_read;
    char stat_path[] = "/proc/self/stat";
    char buffer[4096];
    int len;

    fd = open(stat_path, O_RDONLY);
    if (fd == -1) {
        perror("open stat");
        return -1;
    }

    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read stat");
        close(fd);
        return -1;
    }
    buffer[bytes_read] = '\0';

    close(fd);

    // Parse the ppid field (4th field)
    // The comm field (2nd field) can contain spaces, so find the closing ')'

    // Find the first '('
    char *start = strchr(buffer, '(');
    if (!start) {
        fprintf(stderr, "Malformed stat file: missing '('\n");
        return -1;
    }

    // Find the corresponding ')'
    char *end = strchr(start, ')');
    if (!end) {
        fprintf(stderr, "Malformed stat file: missing ')'\n");
        return -1;
    }

    // The fields after ')' are separated by spaces
    // The ppid is the next field after state, which is the 3rd field
    // So, field 1: pid
    // field 2: comm (in parentheses)
    // field 3: state
    // field 4: ppid

    // Move past ')'
    char *ptr = end + 1;

    // Skip any spaces
    while (*ptr == ' ') ptr++;

    // Now, ptr points to field 3: state
    // Skip field 3
    if (*ptr == '\0') {
        fprintf(stderr, "Malformed stat file: missing state field\n");
        return -1;
    }

    // Skip the state field (single character)
    ptr++;
    while (*ptr == ' ') ptr++;

    // Now, ptr points to field 4: ppid
    if (*ptr == '\0') {
        fprintf(stderr, "Malformed stat file: missing ppid field\n");
        return -1;
    }

    // Read ppid
    errno = 0;
    long ppid_long = strtol(ptr, NULL, 10);
    if (errno != 0) {
        perror("strtol ppid");
        return -1;
    }

    *ppid = (pid_t) ppid_long;
    return 0;
}

/**
 * 親プロセスのコマンド名を /proc/<ppid>/comm から取得する関数
 * 
 * @param ppid 親プロセスのPID
 * @param buffer シェル名を格納するバッファ
 * @param size バッファのサイズ
 * @return 0 成功, -1 失敗
 */
int get_parent_comm(pid_t ppid, char *buffer, size_t size) {
    int fd;
    ssize_t bytes_read;
    char comm_path[256];
    snprintf(comm_path, sizeof(comm_path), "/proc/%d/comm", ppid);

    fd = open(comm_path, O_RDONLY);
    if (fd == -1) {
        perror("open comm");
        return -1;
    }

    bytes_read = read(fd, buffer, size - 1);
    if (bytes_read == -1) {
        perror("read comm");
        close(fd);
        return -1;
    }

    buffer[bytes_read] = '\0';

    close(fd);

    // Remove newline if present
    char *newline = strchr(buffer, '\n');
    if (newline) {
        *newline = '\0';
    }

    return 0;
}

int main() {
    pid_t ppid;
    char parent_comm[256];

    // Step 1: Get ppid from /proc/self/stat
    if (get_ppid_from_stat(&ppid) == -1) {
        write(STDERR_FILENO, "ppidを取得できませんでした。\n", 25);
        return EXIT_FAILURE;
    }

    // Step 2: Get parent process's comm from /proc/<ppid>/comm
    if (get_parent_comm(ppid, parent_comm, sizeof(parent_comm)) == -1) {
        write(STDERR_FILENO, "親プロセスのコマンド名を取得できませんでした。\n", 35);
        return EXIT_FAILURE;
    }

    // Step 3: Write the shell name to stdout
    char *message = "現在のシェル: ";
    write(STDOUT_FILENO, message, strlen(message));
    write(STDOUT_FILENO, parent_comm, strlen(parent_comm));
    write(STDOUT_FILENO, "\n", 1);

    return EXIT_SUCCESS;
}
