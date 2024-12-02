#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    pid_t parent_pid = getppid();
    char proc_path[BUFFER_SIZE];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/comm", parent_pid);

    FILE *file = fopen(proc_path, "r");
    if (file == NULL) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    char comm[BUFFER_SIZE];
    if (fgets(comm, sizeof(comm), file) != NULL) {
        // 改行文字を削除
        size_t len = strlen(comm);
        if (len > 0 && comm[len - 1] == '\n') {
            comm[len - 1] = '\0';
        }
        printf("親プロセスのシェル: %s\n", comm);
    } else {
        printf("親プロセスの情報を取得できませんでした。\n");
    }

    fclose(file);
    return EXIT_SUCCESS;
}
