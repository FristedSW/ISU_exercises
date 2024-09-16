#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // For sleep()

// Shared variable
unsigned int shared = 0;

// Mutex for synchronization
pthread_mutex_t lock;

// Incrementer thread function
void* incrementer(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);  // Lock the mutex
        shared++;  // Increment the shared variable
        pthread_mutex_unlock(&lock);  // Unlock the mutex
        sleep(1);  // Wait for 1 second
    }
    return NULL;
}

// Reader thread function
void* reader(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);  // Lock the mutex
        printf("Shared value: %u\n", shared);  // Read and print the shared variable
        pthread_mutex_unlock(&lock);  // Unlock the mutex
        sleep(1);  // Wait for 1 second
    }
    return NULL;
}

int main() {
    pthread_t inc_thread, reader_thread;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create the incrementer and reader threads
    pthread_create(&inc_thread, NULL, incrementer, NULL);
    pthread_create(&reader_thread, NULL, reader, NULL);

    // Join the threads (in this example, they will run indefinitely)
    pthread_join(inc_thread, NULL);
    pthread_join(reader_thread, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
