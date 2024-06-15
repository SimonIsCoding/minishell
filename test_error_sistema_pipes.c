#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipes[1024][2];
    for (int i = 0; i < 1024; ++i) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

