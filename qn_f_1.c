/*
Name: Ashraf Mohammed Hassan Anil
Reg No: SCT211-0255/2021
UNIT: ICS2305
*/
#include <stdio.h>
#include <signal.h>

volatile sig_atomic_t signal_received = 0;
/*
Defifining a my signal (SIGUSR1) to interact with a running process. 
When the signal is received, the process will prompt the user for input.
*/
void usr_input_signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Custom signal received. Waiting for user input...\n");

        // Set a flag to indicate the signal has been received
        signal_received = 1;
    }
}

int main() {
    signal(SIGUSR1, usr_input_signal_handler);

    printf("Running... Send signal SIGUSR1 to interact with the process.\n");

    while (1) {
        // Check if the signal has been received
        if (signal_received) {
            char input[100];
            printf("Enter a message: ");
            fgets(input, sizeof(input), stdin);
            printf("Received message successfully: %s", input);

            // Reset the flag
            signal_received = 0;
        }
        else{
            /*
            get pid of this program in seperate terminal
            Then use kill -SIGUSR1 <process_id> to send a signal to this program
            that is when loopp stops aks for usr input then terminates with:
            "Received messsage" successfully
            */
            printf("Waiting for signal.... ");
        }
    }

    return 0;
}