/* hello_pthread.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define _GNU_SOURCE
#include <unistd.h>

void *hello_fun(void *args){
    char * str = (char *)args;
    // printf("%s\n", str);
    puts(str);
    printf("TID: %d PID: %d\n", pthread_self(), getpid());
    return NULL;
}

void *hello_fun2(void *args){
    int * str = (int *)args;
    printf("%d\n", *str);
    printf("TID: %d PID: %d\n", pthread_self(), getpid());
    return NULL;
}

int main(int argc, char *argv[]){
    char hello[] = "Hello World";
    int x = 33;
   
    pthread_t t0, t1, t2, t3, t4, t5, t6, t7;
    
    pthread_create(&t0, NULL, hello_fun, "0Hello Word");
    pthread_create(&t1, NULL, hello_fun, "1Hello Word");
    pthread_create(&t2, NULL, hello_fun, "2Hello Word");
    pthread_create(&t3, NULL, hello_fun, "3Hello Word");
    pthread_create(&t4, NULL, hello_fun, "4Hello Word");
    pthread_create(&t5, NULL, hello_fun, "5Hello Word");
    pthread_create(&t6, NULL, hello_fun, "6Hello Word");
    pthread_create(&t7, NULL, hello_fun, "7Hello Word");

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    
    return 0;
}