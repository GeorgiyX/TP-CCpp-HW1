#include <stdio.h>
#include <unistd.h>
#include "module.h"

int switch_to_file() {
    fflush(stdout);
    /* Get file descriptor, associated with original stdout */
    int descriptor_stdout = fileno(stdout);
    if (descriptor_stdout == -1) {
        perror("fileno");
        return -1;
    }
    /* Get copy of file descriptor, associated with original stdout */
    int dup_descriptor_stdout = dup(descriptor_stdout);
    if (dup_descriptor_stdout == -1) {
        perror("dup");
        return -1;
    }
    /* Close original stdout, open "custom_out.txt" stream and associate stdout with it: */
    FILE *file = freopen("custom_out.txt", "a+", stdout);
    if (!file) {
        perror("freopen");
        if (close(dup_descriptor_stdout)) {
            perror("close");
        }
        return -1;
    }
    return dup_descriptor_stdout;
}

int switch_to_terminal(int original_stdout_descriptor) {
    if (original_stdout_descriptor < 0) { return -1; }
    fflush(stdout);
    /* Get file descriptor, associated with current stdout */
    int descriptor_stdout = fileno(stdout);
    if (descriptor_stdout == -1) {
        perror("fileno");
        return -1;
    }
    /* Close the current file descriptor associated with stdout and
     * associate it with the original descriptor */
    if (dup2(original_stdout_descriptor, descriptor_stdout) == -1) {
        perror("dup2");
        return 1;
    }
    if (close(original_stdout_descriptor) == -1) {
        perror("close");
        return 1;
    }
    return 0;
}


int main() {
    printf("Hi stdout!\n");
    int original_descriptor = switch_to_file();
    if (original_descriptor < 0) { return 0; }
    printf("Hi custom_out!\n");
    if (switch_to_terminal(original_descriptor) < 0) { return 0; }
    printf("Hi stdout again!\n");
    return 0;
}
