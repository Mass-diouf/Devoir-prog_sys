#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define N 10  

int value = 0; 
sem_t sem1, sem2; 
int results[2 * N + 1]; 
int index_result = 0;

void* thread1_function(void* arg) 
{
    for (int i = 0; i <= N; i++) 
    {
        sem_wait(&sem1); 
        value++;
        results[index_result++] = value;
        printf("Thread 1: %d\n", value);
        sem_post(&sem2); 
    }
    return NULL;
}

void* thread2_function(void* arg) 
{
    for (int i = 0; i <= N; i++) 
    {
        sem_wait(&sem2); 
        value--;
        results[index_result++] = value;
        printf("Thread 2: %d\n", value);
        sem_post(&sem1); 
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    
    sem_init(&sem1, 0, 1); 
    sem_init(&sem2, 0, 0); 

    
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

   
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

   
    sem_destroy(&sem1);
    sem_destroy(&sem2);

   
    FILE* file = fopen("results.txt", "w");
    if (file) {
        for (int i = 0; i < 2 * N + 1; i++) {
            fprintf(file, "%d\n", results[i]);
        }
        fclose(file);
        printf("Résultats sauvegardés dans 'results.txt'\n");
    } else {
        printf("Erreur d'ouverture du fichier\n");
    }

    return 0;
}

