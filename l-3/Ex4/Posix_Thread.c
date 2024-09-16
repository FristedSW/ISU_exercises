#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>  // For sleep()

// Vector class definition (assuming it's defined in Vector.hpp)
class Vector {
public:
    std::vector<int> elements;

    // Constructor to initialize vector with 10,000 elements
    Vector() : elements(10000, 0) {}

    // Set all elements to a specific value and check consistency
    bool setAndTest(int value) {
        // Set all elements to the value
        for (auto& elem : elements) {
            elem = value;
        }
        
        // Test if all elements hold the same value
        for (const auto& elem : elements) {
            if (elem != value) {
                return false;
            }
        }
        return true;
    }
};

// Structure to hold arguments for thread function
struct ThreadArgs {
    int thread_id;
    Vector* shared_vector;
};

// Mutex for synchronization
pthread_mutex_t lock;

// Writer thread function
void* writer(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int thread_id = args->thread_id;
    Vector* shared_vector = args->shared_vector;

    while (1) {
        // Lock the mutex to ensure only one thread accesses the vector at a time
        pthread_mutex_lock(&lock);
        
        // Set and test the vector
        if (!shared_vector->setAndTest(thread_id)) {
            std::cerr << "Error: Inconsistency detected by thread " << thread_id << std::endl;
        }
        
        // Unlock the mutex after accessing the vector
        pthread_mutex_unlock(&lock);
        
        // Sleep for 1 second before the next iteration
        sleep(1);
    }
    return NULL;
}

int main() {
    const int num_threads = 10;  // Number of writer threads (this can be adjusted)
    pthread_t threads[num_threads];
    ThreadArgs thread_args[num_threads];  // Array to store arguments for each thread

    // Shared Vector object
    Vector shared_vector;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create writer threads
    for (int i = 0; i < num_threads; ++i) {
        thread_args[i].thread_id = i;
        thread_args[i].shared_vector = &shared_vector;
        pthread_create(&threads[i], NULL, writer, (void*)&thread_args[i]);
    }

    // Join the threads (this example runs indefinitely, so it won't return)
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}

