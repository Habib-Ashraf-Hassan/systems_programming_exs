/*
Name: Ashraf Mohammed Hassan Anil
Reg No: SCT211-0255/2021
UNIT : ICS2305
*/
#include <stdio.h>
#include <unistd.h>

int main() {
    // Create a child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        // Fork failed because pid returned is -1
        perror("Fork failed");
        return 1;
    }
    // if not then it means 
    if (child_pid == 0) {
        // This code is executed by the child process since if pid is zero
        //this is the child
        printf("Child process: My PID is %d\n", getpid());
    } else {
        /*
        This code block is executed by the parent process.
        In the parent process, fork() returns the PID of the child process.
        The parent process prints a message indicating that it's the parent process and displays its own PID using getpid().
        It also displays the PID of the child process (the value of child_pid) obtained from the return value of fork(). 
        This is how the parent process knows the PID of the child process it created.
        */
        printf(" Child created successfully !!Parent process: My PID is %d, Child's PID is %d\n", getpid(), child_pid);
    }

    return 0;
}
