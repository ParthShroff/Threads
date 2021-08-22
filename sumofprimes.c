#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* halfSum(void* args){
    int value = *(int*) args;
    int sum = 0;
    for(int i = 0; i < 5; i++){
        sum += primes[value + i];
    }
    int* halfSum = (int*) malloc(sizeof(int));
    *halfSum = sum;
    return (void*) halfSum;
}

int main(int argc, char* argv[]){
    pthread_t th[2];
    int i;
    for(int i = 0; i < 2; i++){
        int* temp = (int*) malloc(sizeof(int));
        *temp = i * 5;
        if(pthread_create(&th[i], NULL, &halfSum, (void*) temp)){ 
            perror("Error in thread creation");
        }
    }
    
    int globalSum = 0;
    for(int i = 0; i < 2; i++){
        int* halfSum;
        if(pthread_join(th[i], (void**) &halfSum)){
            perror("Error in thread joining");
        }
        globalSum += *halfSum;
        free(halfSum);
    }
    printf("global sum: %d \n", globalSum);
    return 0;
}
