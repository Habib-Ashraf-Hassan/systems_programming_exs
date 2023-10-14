/*
Name: Ashraf Mohammed Hassan Anil
Reg No: SCT211-0255/2021
UNIT : ICS2305
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //it defines the pid_t data type, which is commonly used to represent process IDs (PIDs).
#include <sys/wait.h>  //The waitpid function is declared in this header.
#include <unistd.h>

int main() {
    pid_t child_pid;
    int status;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process: My PID is %d\n", getpid());
        exit(42); // Child exits with status 42
    } else {
        // This code is executed by the parent process
        printf("Parent process: My PID is %d\n", getpid());

        // Wait for the child process to terminate and get its termination status
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Parent: Child process exited with status %d\n", exit_status);
        } else {
            printf("Parent: Child process did not exit normally\n");
        }
    }

    return 0;
}
