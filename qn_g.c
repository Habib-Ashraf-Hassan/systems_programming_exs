/*
Name: Ashraf Mohammed Hassan Anil
Reg No: SCT211-0255/2021
UNIT: ICS2305
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// File creation and signal handler
void create_file_and_schedule_deletion() {
    FILE *file;
    file = fopen("JUJU.txt", "w");
    if (file == NULL) {
        perror("File creation error");
        exit(1);
    }
    fclose(file);

    // Schedule the file for deletion in 5 seconds
    alarm(5);
}

// Signal handler for SIGALRM
void handle_alarm_signal(int signum) {
    if (signum == SIGALRM) {
        if (remove("JUJU.txt") == 0) {
            printf("File 'JUJU.txt' has been successfully deleted.\n");
        } else {
            perror("File deletion error");
        }
        exit(0);
    }
}

int main() {
    signal(SIGALRM, handle_alarm_signal);
    
    // Create the file and schedule its deletion
    create_file_and_schedule_deletion();

    // Keep the program running
    while (1) {
        sleep(1);
    }

    return 0;
}
