#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler function 
void handle_signal(int sig) {
    if (sig == SIGINT) {
        printf("\nMonitor Service shutting down safely.\n");
        exit(0);
    } else if (sig == SIGUSR1) {
        printf("\nSystem status requested by administrator.\n");
    } else if (sig == SIGTERM) {
        printf("\nEmergency shutdown signal received.\n");
        exit(0);
    }
}

// Main function
int main() {
    // Register the signal handlers 
    signal(SIGINT, handle_signal);
    signal(SIGUSR1, handle_signal);
    signal(SIGTERM, handle_signal);

    // Print process ID to allow user know what to target with the kill command
    printf("Monitor Service started. PID: %d\n", getpid());
    printf("Waiting for signals... (Press Ctrl+C for SIGINT)\n\n");

    // Run continuously 
    while (1) {
        printf("[Monitor Service] System running normally...\n");
        sleep(5);
    }

    return 0;
}
