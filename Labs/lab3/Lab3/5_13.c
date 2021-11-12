#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE * stream = fopen(argv[1], "r");

    char line[1024];
    int i = 0;

    while (fgets(line, 1024, stream) && i < 10){
        printf("%s", line);
        i++;
    }

    fclose(stream);
    return 0;
}