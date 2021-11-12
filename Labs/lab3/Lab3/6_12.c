#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE * stream = fopen("processes.dat", "r");

    char line[1024];
    int process_id;
    char name[200];
    float duration;
    int priority;

    while (fgets(line, 1024, stream)){
        char* token = strtok(line, ":");
        token = strtok(NULL, ":");
        strcpy(name, token);
        token = strtok(NULL, ":");
        token = strtok(NULL, ":");
        priority = atoi(token);
        printf("process name: %s, priority: %d\n", name, priority);
    }

    fclose(stream);
    return 0;
}