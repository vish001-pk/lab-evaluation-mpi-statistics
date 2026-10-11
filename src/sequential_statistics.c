
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    long long N = 1000000;
    long long i, value;
    long long sum = 0, min = 1001, max = 0;
    double average, elapsed;
    clock_t start, end;

    if (argc > 1)
        N = atoll(argv[1]);

    if (N <= 0) {
        printf("Error: dataset size must be positive.\n");
        return 1;
    }

    start = clock();

    for (i = 0; i < N; i++) {
        value = (i % 1000) + 1;
        sum += value;

        if (value < min) min = value;
        if (value > max) max = value;
    }

    end = clock();

    average = (double)sum / N;
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nSequential Dataset Statistics\n");
    printf("------------------------------\n");
    printf("Dataset size : %lld\n", N);
    printf("Sum          : %lld\n", sum);
    printf("Average      : %.3f\n", average);
    printf("Minimum      : %lld\n", min);
    printf("Maximum      : %lld\n", max);
    printf("Elapsed time : %.6f seconds\n", elapsed);

    return 0;
}
