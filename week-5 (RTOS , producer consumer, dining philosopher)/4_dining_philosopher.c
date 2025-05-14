#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Dining Philosophers
sem_t forks[2];

void* philosopher(void* arg) {
    int id = *(int*)arg;

    printf("Philosopher %d is thinking.\n", id);
    sleep(1);

    sem_wait(&forks[0]);
    sem_wait(&forks[1]);

    printf("Philosopher %d is eating.\n", id);
    sleep(1);

    sem_post(&forks[0]);
    sem_post(&forks[1]);
    printf("Philosopher %d finished eating.\n", id);
    return NULL;
}

void main() {
    pthread_t phil;
    int id = 1;

    sem_init(&forks[0], 0, 1);
    sem_init(&forks[1], 0, 1);

    pthread_create(&phil, NULL, philosopher, &id);
    pthread_join(phil, NULL);

    sem_destroy(&forks[0]);
    sem_destroy(&forks[1]);
}

/*
Philosopher 1 is thinking.
Philosopher 1 is eating.
Philosopher 1 finished eating.*/
