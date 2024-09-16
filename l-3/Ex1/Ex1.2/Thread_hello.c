#include <stdio.h>
#include <pthread.h>

// Function to be executed by the thread
void* print_hello(void* arg) {
    printf("Hello, world\n");
    return NULL;
}

int main() {
    pthread_t thread;

    // Create a new thread that runs the print_hello function
    pthread_create(&thread, NULL, print_hello, NULL);

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    return 0;
}
