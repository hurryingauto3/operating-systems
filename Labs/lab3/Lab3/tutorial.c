#include <stdio.h>

void print_table (int num){
   int i = 0;
   for (i = 1; i <= 10; i++)
      printf("%d x %d = %d\n", num, i, num*i);
}

int main(){
    int i = 0;
    int num = 0;
    float gpa = 0.0;
    char name[20];

    printf("Enter your name:\n");
    scanf("%s", name);

    printf("Enter your gpa:\n");
    scanf("%f", &gpa);
    
    printf("Enter your num:\n");
    scanf("%d", &num);

    printf("Welcome %s (gpa=%f)!", name, gpa);
    printf("Here's your table:\n");
    print_table(num);

    printf("The End.\n");
    return 0;
}
