#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // For sleep()

// Function for the thread to run
void* thread_function(void* arg) {
    int thread_id = *((int*)arg);  // Get thread ID

    for (int i = 0; i < 10; ++i) {
        printf("Hello #%d from thread %d\n", i, thread_id);
        sleep(1);  // Sleep for 1 second
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;  // Declare two thread objects
    int thread1_id = 1, thread2_id = 2;

    printf("Main: Creating threads\n");

    // Create thread 1
    pthread_create(&thread1, NULL, thread_function, &thread1_id);
    // Create thread 2
    pthread_create(&thread2, NULL, thread_function, &thread2_id);

    printf("Main: Waiting for threads to finish\n");

    // Wait for thread 1 to finish
    pthread_join(thread1, NULL);
    // Wait for thread 2 to finish
    pthread_join(thread2, NULL);

    printf("Main: Exiting\n");

    return 0;
}
