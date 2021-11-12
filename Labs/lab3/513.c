#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE * head = fopen(argv[1], "r");

    char line[1024];
    int i = 0;

    for (i; i < 10; i++){
      if (fgets(line, 1024, head)){
        printf("%s\n", line);

      }
    }


    fclose(head);
    return 0;
}
