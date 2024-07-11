#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, blank_count = 0;
    char buffer[1];

    fd = open("your_file.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    while (read(fd, buffer, 1) > 0) {
        if (buffer[0] == ' ') {
            blank_count++;
        }
    }
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    printf("Number of blanks in the file: %d\n", blank_count);

    return 0;
}
