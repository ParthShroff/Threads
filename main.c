#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int counter = 0;
pthread_mutex_t mutex;

void* func(){
    for(int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&mutex); //Sets the lock so that an additional thread cannot access this shared resource
        counter++;
        pthread_mutex_unlock(&mutex);
    }
}

void* rollDice(){
    int value = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    return (void*) result;
}

int main(int argc, char* argv[]){

    int* res;
    pthread_t threads[4];
    pthread_t threadDice[4];

    for(int i = 0; i < 4; i++){
        if(pthread_create(&threads[i], NULL, &func, NULL) != 0){
            perror("Failed to create thread normal \n");
            return 1;
        }
        printf("Thread normal %d started \n", i);
        if(pthread_create(&threadDice[i], NULL, &rollDice, NULL) != 0){
            perror("Failed to create thread dice \n");
            return 1;
        }
        printf("Thread dice %d started \n", i);
    }

    
    for(int i = 0; i < 4; i++){
        if (pthread_join(threads[i], NULL) != 0){
            return 2;
        }
        printf("Thread %d ended \n", i);
        if (pthread_join(threadDice[i], (void**) &res) != 0){
            return 2;
        }
        printf("Result %d \n", *res);
    }
    pthread_mutex_init(&mutex, NULL);

    pthread_mutex_destroy(&mutex);
    printf("number of mails: %d\n", counter);
    free(res);
    return 0;
}
