#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  
    FILE * copyfrom = fopen(argv[1], "r");
    FILE * copyto = fopen(argv[2], "w");

    char line[1024];

    while (fgets(line, 1024, copyfrom)){
        fprintf(copyto, "%s", line);
    }

    fclose(copyfrom);
    fclose(copyto);

    return 0;
}
