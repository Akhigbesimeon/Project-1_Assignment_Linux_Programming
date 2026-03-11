#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void sync_files(const char *src, const char *dest) {
    int fd_src = open(src, O_RDONLY);
    if (fd_src < 0) return;

    int fd_dest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0) {
        close(fd_src);
        return;
    }

    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(fd_src, buffer, sizeof(buffer))) > 0) {
        write(fd_dest, buffer, bytes_read);
    }

    close(fd_src);
    close(fd_dest);
}

// Main function
int main(int argc, char *argv[]) {
    puts(" Starting data_sync agent...");
    
    FILE *config = fopen("/etc/data_sync.conf", "r");
    if (config) {
        puts("Configuration loaded.");
        fclose(config);
    }

    sync_files("/tmp/source_data.bin", "/tmp/backup_data.bin");
    
    puts("Synchronization complete.");
    return 0;
}
