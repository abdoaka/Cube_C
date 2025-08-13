#include "get_next_line.h"


#include <fcntl.h>

int main() {
    int fd;
    char *line;

    // Open the file in read-only mode
    int fd = open("path/to/your/test.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Read lines one by one
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);  // Print the line
        free(line);  // Free the memory allocated for the line
    }

    close(fd);  // Close the file descriptor
    return 0;
}