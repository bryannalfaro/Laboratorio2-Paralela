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

int compare(const int *a, const int *b)
{
    return (*(int *)a - *(int *)b);
}

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
    par_qsort(data, lo, h);
    par_qsort(data, l, hi);
}

int main(int argc, char *argv[])
{

    // receive N from command line
    int n = atoi(argv[1]);
    if (n == 0)
        n = 10;
    int Array[n];
    int j;
    srand(time(NULL)); // To get random every time
    // measure time for sequential in omp
    double start = omp_get_wtime();

    for (j = 0; j < n; j++)

        Array[j] = rand() % n;

    // Open the file in write mode
    FILE *fp;
    fp = fopen("aleatorios.csv", "w");
    if (fp == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    // Write to file
    for (j = 0; j < n - 1; j++)
    {
        fprintf(fp, "%d,", Array[j]);
    }
    fprintf(fp, "%d", Array[n - 1]);
    fclose(fp);

    // Open the file in read mode
    FILE *fp2;
    fp2 = fopen("aleatorios.csv", "r");
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
    par_qsort(Array, 0, n - 1);

    // Write into another file
    FILE *fp3;
    fp3 = fopen("ordenados.csv", "w");
    if (fp3 == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    for (j = 0; j < n - 1; j++)
    {
        fprintf(fp3, "%d,", Array[j]);
    }
    fprintf(fp3, "%d", Array[n - 1]);
    fclose(fp3);

    double end = omp_get_wtime();
    printf("Time: %f", end - start);

    return 0;
}