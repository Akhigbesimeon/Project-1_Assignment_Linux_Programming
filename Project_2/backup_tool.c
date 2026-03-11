#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Write log
void write_log(const char *message) {
    int log_fd = open("backup.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (log_fd >= 0) {
        write(log_fd, message, strlen(message));
        close(log_fd);
    }
}

// Main function
int main() {
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[4096];
    const char *initial_data = "Important system data that needs to be backed up.\n";

    write_log("Backup process initiated.\n");

    // File creation
    src_fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (src_fd < 0) {
        perror("Error creating data.txt");
        exit(EXIT_FAILURE);
    }
    write(src_fd, initial_data, strlen(initial_data));
    close(src_fd);
    write_log("Source file data.txt created.\n");

    // Read file and create a backup copy
    src_fd = open("data.txt", O_RDONLY); 
    if (src_fd < 0) {
        perror("Error opening data.txt for reading");
        exit(EXIT_FAILURE);
    }

    dest_fd = open("data.backup", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error creating data.backup");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // Copy loop
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to data.backup");
            break;
        }
    }

    close(src_fd);
    close(dest_fd);

    write_log("Backup successfully copied to data.backup.\n");

    return 0;
}
