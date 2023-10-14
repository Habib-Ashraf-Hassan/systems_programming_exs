/*
Name: Ashraf Mohammed Hassan Anil
Reg No: SCT211-0255/2021
UNIT : ICS2305
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
/*
dirent.h was used for directory listing and access to process info
used sys/stat.h  to use the S_ISDIR macro from the <sys/stat.h> header. 
*/

int main() {
    DIR *dp;
    struct dirent *entry;
    char path[1024]; // Use a larger buffer to accommodate long paths
    //open the /proc dir 
    dp = opendir("/proc");
    // if the /proc directory is empty output an error message
    if (dp == NULL) {
        perror("opendir");
        exit(1);
    }
    //output as the PID, Priority and Parent pid as column headers
    printf("%-10s %-15s %-10s\n", "PID", "PRIORITY", "PPID");

    while ((entry = readdir(dp))) {
        snprintf(path, sizeof(path), "/proc/%s", entry->d_name);

        struct stat st;
        // Construct the full path to the process directory
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
            int pid = atoi(entry->d_name);

            if (pid > 0) {
                char stat_path[100];
                //Construct the full path to the process's stat file
                snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);

                FILE *stat_file = fopen(stat_path, "r");
                if (stat_file) {
                    int c;
                    int ppid, priority;

                    // Extract data from the stat file
                    // Format: pid , status, ppid,  priority ...
                    fscanf(stat_file, "%*d %*s %*c %d %d", &ppid, &priority);

                    fclose(stat_file);

                    // Print the information
                    printf("%-10d %-15d %-10d\n", pid, priority, ppid);
                }
            }
        }
    }

    closedir(dp);

    return 0;
}
