#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_HUNTS 10
#define MAX_BUFFER 256

pid_t monitor_pid = -1; // PID of the background monitor process

// Function prototypes
void start_monitor();
void list_hunts();
void stop_monitor();
void signal_handler(int sig);
void cleanup();

int main() {
    char command[MAX_BUFFER];
    signal(SIGCHLD, signal_handler); // Handle termination of child processes
    atexit(cleanup); // Ensure cleanup on program exit

    printf("Welcome to Treasure Hub!\n");
    printf("Commands:\n");
    printf("  start_monitor - Start background hunt monitoring\n");
    printf("  list_hunts - List all hunts (mock data)\n");
    printf("  stop_monitor - Stop the monitor process\n");
    printf("  exit - Exit the program\n");

    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; // Remove newline

        if (strcmp(command, "start_monitor") == 0) {
            start_monitor();
        } else if (strcmp(command, "list_hunts") == 0) {
            list_hunts();
        } else if (strcmp(command, "stop_monitor") == 0) {
            stop_monitor();
        } else if (strcmp(command, "exit") == 0) {
            if (monitor_pid > 0) {
                printf("Please stop the monitor process before exiting.\n");
            } else {
                break;
            }
        } else {
            printf("Unknown command.\n");
        }
    }

    return 0;
}

// Start the monitor process
void start_monitor() {
    if (monitor_pid > 0) {
        printf("Monitor process is already running.\n");
        return;
    }
    monitor_pid = fork();
    if (monitor_pid < 0) {
        perror("Failed to start monitor");
        return;
    }

    if (monitor_pid == 0) {
        // Child process: Simulate hunt monitoring
        while (1) {
            printf("Monitor: Monitoring hunts...\n");
            sleep(3); // Simulate periodic monitoring
        }
        exit(0); // Child process exits
    } else {
        printf("Monitor process started (PID: %d).\n", monitor_pid);
    }
}