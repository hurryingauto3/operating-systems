#include <stdio.h>
#include <string.h>

int my_strlen(const char* string){
    int length = 0;
    while(*(string + length) != '\0')
    {
        length++;
    }
    return length;
}

char* my_strcpy(char* s2, const char* s1){
    int length = 0;
    while(*(s1 + length) != '\0')
    {
        *(s2 + length) = *(s1 + length);
        length++;
    }
    *(s2 + length) = '\0';
    return s2;
}

int my_strcmp(const char* s1, const char* s2){
    int length = 0;
    while(*(s1 + length) != '\0' && *(s2 + length) != '\0')
    {
        if (*(s1 + length) == *(s2 + length)) {length++;}
        else if (*(s1 + length) > *(s2 + length)) {return 1;}
        else {return -1;}

        if (*(s1 + length) != '\0' && *(s2 + length) == '\0') {return 1;}
        if (*(s1 + length) == '\0' && *(s2 + length) != '\0') {return -1;}
    }
    return 0;
}

int main(){
    const char* s1 = "hello world!\n";
    const char* s2 = "bye, bye!\n";
    char s3[20];

    //get string length
    int len1 = my_strlen(s1);
    int len2 = strlen(s1);
    printf("the length of string \"hello world!\\n\" using my_strlen is %d\n", len1);
    printf("the length of string \"hello world!\\n\" using strlen is %d\n", len2);

    //copy a string
    my_strcpy(s3, s1);
    printf("the source string was %s", s1);
    printf("the destination string was %s", s3);

    //compare two strings
    if (my_strcmp(s1, s3) == 0)
    {
        printf("the string was succesfully copied");
    }
    else
    {
        printf("something went wrong with func my_strcmp");
    }
    return 0;
}