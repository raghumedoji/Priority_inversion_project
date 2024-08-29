#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Define a global mutex
pthread_mutex_t mutex;

// high-priority, medium-priority, and low-priority threads
void* high_priority_thread(void* arg) {
    pthread_mutex_lock(&mutex);
    printf("High Priority Thread: Locked mutex, performing work...\n");
    sleep(2); // Simulate work
    printf("High Priority Thread: Work done, unlocking mutex...\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* medium_priority_thread(void* arg) {
    printf("Medium Priority Thread: Attempting to lock mutex...\n");
    pthread_mutex_lock(&mutex);
    printf("Medium Priority Thread: Locked mutex, performing work...\n");
    sleep(2); // Simulate work
    printf("Medium Priority Thread: Work done, unlocking mutex...\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* low_priority_thread(void* arg) {
    printf("Low Priority Thread: Performing work...\n");
    sleep(1); // Simulate work
    printf("Low Priority Thread: Work done.\n");
    return NULL;
}

int main() {
    pthread_t threads[3];

    // Initialize the mutex with priority inheritance
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    
    pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
    pthread_mutex_init(&mutex, &attr);

    // Create threads with different priorities
    pthread_create(&threads[0], NULL, high_priority_thread, NULL);
    pthread_create(&threads[1], NULL, medium_priority_thread, NULL);
    pthread_create(&threads[2], NULL, low_priority_thread, NULL);

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&attr);

    return 0;
}
