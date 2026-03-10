#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate syncing by copying data from one file to another
void sync_files(const char* source, const char* destination) {
    FILE *f_src = fopen(source, "rb");
    if (f_src == NULL) {
        printf("[ERROR] Cannot open source file.\n");
        return;
    }

    FILE *f_dest = fopen(destination, "wb");
    if (f_dest == NULL) {
        printf("[ERROR] Cannot open destination file.\n");
        fclose(f_src);
        return;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), f_src)) > 0) {
        fwrite(buffer, 1, bytes_read, f_dest);
    }

    fclose(f_src);
    fclose(f_dest);
    printf("[INFO] Synchronization complete.\n");
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }
    
    sync_files(argv[1], argv[2]);
    return 0;
}
