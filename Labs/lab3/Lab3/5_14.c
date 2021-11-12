#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE * copiedfile = fopen(argv[1], "r");
    FILE * newfile = fopen(argv[2], "w");

    char line[1024];

    while (fgets(line, 1024, copiedfile)){
        fprintf(newfile, "%s", line);
    }

    fclose(copiedfile);
    fclose(newfile);
    return 0;
}