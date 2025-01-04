#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1;

void *afficher1(void *arg) {
    int n = *(int *)arg;
    
    for (int i = 1; i <= n; i++) {
        
        printf("%d \n", i);
      
    }
    sem_post(&sem1);
    return NULL;
}

void *afficher2(void *arg) {
    int n = *(int *)arg;
    sem_wait(&sem1);
    for (int i = -1; i >= -n; i--) {
       
        printf("%d \n", i);
        
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;
    int n = 4;

    // Initialisation des sémaphores
    sem_init(&sem1, 1, 0); 
    pthread_create(&p1, NULL, afficher1, &n);
    pthread_create(&p2, NULL, afficher2, &n);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Fin du programme\n");

   
    sem_destroy(&sem1);
  

    return 0;
}

