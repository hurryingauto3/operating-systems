#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * stream = fopen("students.dat", "r");
    FILE * stream2 = fopen("helloworld.txt", "a");

    char iD[1024], lname[1024];
    int a;
    float b;
    char c;

    while (fscanf(stream, 
                    "%s %s %d %f %c", 
                    iD, lname, &a, &b, &c) != EOF){
        fprintf(stream2, "ID: %s\n", iD);
        fprintf(stream2, "Name: %s\n", lname);
        fprintf(stream2, "Marks: %d\n", a);
        fprintf(stream2, "gpa: %f\n", b);
        fprintf(stream2, "grade: %c\n", c);
    }

    fclose(stream);
    fclose(stream2);
    return 0;
}