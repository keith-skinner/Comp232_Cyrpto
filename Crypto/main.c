#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LSIZ 401
#define RSIZ 401

void primeFactor(int num, int k, FILE *files[])
{
#pragma omp parallel
    {
        for (int i = 2; i <= num; i++) {
            /* Check 'i' for factor of num */
            if (num % i == 0)
            {
                /* Check 'i' for Prime */
                int isPrime = 1;
                #pragma omp single
                for (int j = 2; j <= i / 2; j++)
                {
                    if (i % j == 0) {
                        isPrime = 0;
                        break;
                    }
                }

                /* If 'i' is Prime number and factor of num */
                #pragma omp single
                if (isPrime == 1)
                {
                    fprintf(files[k], "%d  ", i);
                }
            }
        }
    }
}
int main()
{
    int numfiles=400;
    char line[RSIZ][LSIZ];
    //char fname[20];
    FILE *fptr = NULL;
    FILE *files[numfiles];
    int i=0;
    int tot = 0;
    int num;
    int number[RSIZ];
    char filename[40];

    fptr = fopen("../semi.txt", "r");
    time_t start=clock();
    while(fgets(line[i], LSIZ, fptr))
    {
        line[i][strlen(line[i]) ] = '\0';
        i++;
    }
    tot=i;
    for(i = 0; i < tot; i++)
    {
        number[i]=atoi(line[i]);

        // printf(" %d\n", number[i]);
    }

        for (int k = 0; k < tot; k++) {
            sprintf(filename, "../outputs/Factors%d.txt", k);
            files[k] = fopen(filename, "w");
            num = number[k];

            primeFactor(num, k, files);

        }

    fclose(fptr);
    time_t end=clock();
    double time=(double) (end-start) ;
    printf("Execution time was %.1f \n",time);
    return 0;

}