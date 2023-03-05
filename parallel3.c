/*
Laboratorio 2
Bryann Alfaro
Osmin Orellana

Referencias:
https://www.geeksforgeeks.org/basics-file-handling-c/
https://www.programiz.com/c-programming/c-file-input-output
Codigo proporcionado como base
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

void par_qsort(int *data, int lo, int hi)
{
    if (lo > hi)
        return;
    int l = lo;
    int h = hi;
    int p = data[(hi + lo) / 2];
    while (l <= h)
    {
        while ((data[l] - p) < 0)
            l++;

        while ((data[h] - p) > 0)
            h--;

        if (l <= h)
        {
            // swap
            int tmp = data[l];
            data[l] = data[h];
            data[h] = tmp;
            l++;
            h--;
        }
    }
    // recursive call
#pragma omp task shared(data)
    par_qsort(data, lo, h);

#pragma omp task shared(data)
    par_qsort(data, l, hi);
}
int main(int argc, char *argv[])
{
    // receive N from command line
    int n = atoi(argv[1]);
    int thread_count = atoi(argv[2]);
    double seq_time = 0.5846;
    if (n == 0)
        n = 10;
    if (thread_count == 0)
        thread_count = 8;

    int Array[n];
    int j;
    srand(time(NULL));
    // measures time
    double start = omp_get_wtime();

#pragma omp parallel for num_threads(thread_count)
    for (j = 0; j < n; j++)

        Array[j] = rand() % n;

    // Open the file in write mode
    FILE *fp;
    fp = fopen("aleatorios_p.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

// Write to file
#pragma omp parallel for num_threads(thread_count)
    for (j = 0; j < n - 1; j++)
    {
        fprintf(fp, "%d,", Array[j]);
    }
    fprintf(fp, "%d", Array[n - 1]);
    fclose(fp);

    // Open the file in read mode
    FILE *fp2;
    fp2 = fopen("aleatorios_p.csv", "r");
    if (fp2 == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
    int i = 0;
    char ch;
    // Read with fscanf
    while (fscanf(fp2, "%d,", &Array[i]) != EOF)
    {
        i++;
    }

    fclose(fp2);

// Sort array
#pragma omp parallel
    {
#pragma omp single
        {
            par_qsort(Array, 0, n - 1);
        }
    }
    // Write into another file
    FILE *fp3;
    fp3 = fopen("ordenados_p.csv", "w");
    if (fp3 == NULL)
    {
        printf("Error opening file");
        exit(1);
    }
#pragma omp sections
    {
#pragma omp section
        {
            for (j = 0; j < n - 1; j++)
            {

                fprintf(fp3, "%d,", Array[j]);
            }
            fprintf(fp3, "%d", Array[n - 1]);

            fclose(fp3);
        }
    }
    double end = omp_get_wtime();
    printf("Time: %f\n", end - start);
    printf("Speedup: %f\n", seq_time / (end - start));
    // Efficiency
    printf("Efficiency: %f", (seq_time / (end - start)) / thread_count);

    return 0;
}