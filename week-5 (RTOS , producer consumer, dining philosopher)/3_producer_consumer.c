#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
// Producer-Consumer 
int buffer;
sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item = rand() % 100;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    buffer = item;
    printf("Producer produced: %d\n", item);

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    return NULL;
}

void* consumer(void* arg) {
    int item;
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    item = buffer;
    printf("Consumer consumed: %d\n", item);

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return NULL;
}

void main() {
    pthread_t p, c;
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}
