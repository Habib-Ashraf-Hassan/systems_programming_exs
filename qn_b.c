/*
Name: Ashraf Mohammed Hassan Anil
Reg No: SCT211-0255/2021
UNIT : ICS2305
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main() {
    const char *scriptName = "NYONGA.sh";
    char command[100];

    // Get the PID of the "NYONGA.sh" script by its name
    snprintf(command, sizeof(command), "pgrep -x %s", scriptName);
    FILE *pid_file = popen(command, "r");
    if (pid_file == NULL) {
        perror("popen");
        return 1;
    }
    
    pid_t script_pid;
    if (fscanf(pid_file, "%d", &script_pid) == 1) {
        // Terminate the script using its PID
        if (kill(script_pid, SIGTERM) == 0) {
            printf("The %s script was successfully killed.\n", scriptName);
        } else {
            printf("Failed to kill the %s script.\n", scriptName);
        }
    } else {
        printf("The %s script is not running.\n", scriptName);
    }
    
    pclose(pid_file);

    return 0;
}


