#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int* createArray(int size){
    int a[size];
    for(int i = 0; i < size; i++){
        a[i] = i^2;
    }
    return a;
}
int normalSum(int *array){
    int sum = 0;
    for(int i = 0; i < sizeof(array); i++){
        sum += array[i];
    }
    return sum;
}

int threadedSum(int *array, int s0, int sf){
    int sum = 0;
    for(int i = s0; i < sf; i++){
        sum += array[i];
    }
    return sum;
}

int main(int argc, char *argv[]){
    return normalSum(createArray(1000));
}
