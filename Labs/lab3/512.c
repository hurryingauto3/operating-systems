#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv){
  FILE * stream = fopen("student.dat", "r");
  FILE * append = fopen("helloworld.txt", "a");

  char iD[1024];
  char lname[1024];
  int a;
  float b;
  char c;

  while (fscanf(stream,
            "%s %s %d %f %c",
            iD, lname, &a, &b, &c) != EOF ){
              fprintf(append,"ID: %s\n", iD);
              fprintf(append,"Name: %s\n", lname );
              fprintf(append,"marks: %d\n", a);
              fprintf(append,"gpa: %f\n", b);
              fprintf(append,"grade: %c\n", c);
              fprintf(append,"\n");
            }
  fclose(append);
  fclose(stream);

  return 0;

}
