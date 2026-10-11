
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    long long N = 1000000;
    long long i, start, end, local_n;
    long long local_sum = 0, global_sum = 0;
    long long local_min = 0, global_min = 0;
    long long local_max = 0, global_max = 0;
    double start_time, end_time, elapsed, max_elapsed;
    double average;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc > 1) {
        N = atoll(argv[1]);
    }

    if (N <= 0) {
        if (rank == 0)
            printf("Error: dataset size must be positive.\n");
        MPI_Finalize();
        return 1;
    }

    start_time = MPI_Wtime();

    /* Divide the dataset across processes. */
    start = (N / size) * rank;
    end = (N / size) * (rank + 1);

    if (rank == size - 1)
        end = N;

    local_n = end - start;

    if (local_n > 0) {
        local_min = 1001;
        local_max = 0;

        for (i = start; i < end; i++) {
            long long value = (i % 1000) + 1;

            local_sum += value;

            if (value < local_min)
                local_min = value;

            if (value > local_max)
                local_max = value;
        }
    } else {
        local_min = 1001;
        local_max = 0;
    }

    MPI_Reduce(&local_sum, &global_sum, 1,
               MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_min, &global_min, 1,
               MPI_LONG_LONG, MPI_MIN, 0, MPI_COMM_WORLD);

    MPI_Reduce(&local_max, &global_max, 1,
               MPI_LONG_LONG, MPI_MAX, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();
    elapsed = end_time - start_time;

    MPI_Reduce(&elapsed, &max_elapsed, 1,
               MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        average = (double)global_sum / N;

        printf("\nDistributed Dataset Statistics\n");
        printf("--------------------------------\n");
        printf("Dataset size : %lld\n", N);
        printf("MPI processes: %d\n", size);
        printf("Sum          : %lld\n", global_sum);
        printf("Average      : %.3f\n", average);
        printf("Minimum      : %lld\n", global_min);
        printf("Maximum      : %lld\n", global_max);
        printf("Elapsed time : %.6f seconds\n", max_elapsed);
    }

    MPI_Finalize();
    return 0;
}
