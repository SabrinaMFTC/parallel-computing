/*
    Compile with gcc parallelSearch.c -o parallelSearch -fopenmp
    1st Run: time -p ./parallelSearch
    2nd Run: time -p OMP_NUM_THREADS=1 ./parallelSearch
    3rd Run: time -p OMP_NUM_THREADS=2 ./parallelSearch
    4th Run: time -p OMP_NUM_THREADS=4 ./parallelSearch
    5th Run: time -p OMP_NUM_THREADS=8 ./parallelSearch
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define SIZE 1073741824

int a[SIZE];

int main() {
    // Reset the seed to generate a different number each run
    srand(time(NULL));

    // Generate a random number to search for in the array
    int number = rand() % SIZE;
    printf("Number = %d\n", number);

    // Fill the array with different values
    for (int i = 0; i < SIZE; ++i) a[i] = i;

    // Max number of threads
    int max = omp_get_max_threads();
    printf("Max number of threads = %d\n", max);

    // Parallel region
    #pragma omp parallel
    {
        printf("=======================================================\n");

        // Thread ID
        int id = omp_get_thread_num();
        printf("Thread ID = %d\n", id);

        // Number of threads
        int num_threads = omp_get_num_threads();

        // Size of each slot per thread
        int slot = SIZE / num_threads;
        printf("Slot size: %d / %d = %d\n", SIZE, num_threads, slot);

        if (slot == 0) printf("The loop won't start since slot's size is 0.\n");
        else {
            // Thread start and end
            int start = id * slot;
            int end = start + slot;

            for (int i = start; i < end; ++i) {
                if (a[i] == number) {
                    printf("Number %d found with thread %d at position %d\n", number, id, i);
                }
            }
        }
    }

    return 0;
}
