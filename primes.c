#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* args){
    int value = *(int*) args;
    printf("%d ", value);
}

int main(int argc, char* argv[]){
    pthread_t th[10];
    int i;
    for(int i = 0; i < 10; i++){
        if(pthread_create(&th[i], NULL, &routine, primes + i)){ 
            perror("Error in thread creation");
        }
    }
    
    for(int i = 0; i < 10; i++){
        if(pthread_join(th[i], NULL)){
            perror("Error in thread joining");
        }
    }
}
