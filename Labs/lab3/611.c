#include <stdio.h>
#include <string.h>

int my_strlen(const char* s){
  char* t;
  int len = 0;

  while(*(s + len) !='\0'){
    len++;
  }

  return len;
}

char* my_strcpy(const char* s0, char* s1){
  int len = 0;
  while(*(s0 + len) !='\0'){
    *(s1 + leng) = *(s0 + len);
    len++;
  }
  *(s1 + len) = '\0';
  return s1;
}

int my_strcmp(const char* s0, const char* s1){

  int len = 0;
  while(*(s0 + len) !='\0' && *(s1+ len) != '\0'){

    if (*(s0 + len) == *(s1 + len))
      len++;
    else if(*(s0 + len) > *(s1 + len)){
      return 1;
    }
    else return -1;

    if (*(s0 + len) != *(s1 + len) && *(s1 + len) == '\0')
      return 1;
    if (*(s0 + len) == '\0' && *(s1+ len) != '\0')
      return -1;

  }

}
