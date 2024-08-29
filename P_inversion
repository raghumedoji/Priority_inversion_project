#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Mutex and attributes
pthread_mutex_t mutex;
pthread_mutexattr_t attr;

void* thread_routine(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("Thread %ld: Acquired mutex.\n", (long)arg);
    // Simulate some work
    sleep(2);
    printf("Thread %ld: Releasing mutex.\n", (long)arg);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[2];

    // Initialize mutex attributes
    pthread_mutexattr_init(&attr);
    // Set the priority inheritance protocol
    pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
    // Initialize the mutex with the attributes
    pthread_mutex_init(&mutex, &attr);

    // Create threads
    pthread_create(&threads[0], NULL, thread_routine, (void*)1);
    pthread_create(&threads[1], NULL, thread_routine, (void*)2);

    // Wait for threads to complete
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex and attributes
    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&attr);

    return 0;
}
