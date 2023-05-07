#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
struct timespec start, finish;
double elapsed;
int n,rg1,cg1,rg2,cg2;
int ig=0;
int jg=0;
int l=0;
int mg1[1024][1024];
int mg2[1024][1024];
int resg[1024][1024];

void mulElement(void *var)
{

calc2:
    if(ig < rg1)
    {
        if(jg < cg2)
        {
            goto calc;
        }
        printf("\n");
        ig++;
        jg=0;
        goto calc2;
    }
    goto jmp;
calc:
    resg[ig][jg] = 0;

    for (l=0; l < rg2; l++)
    {
        resg[ig][jg] =resg[ig][jg] + mg1[ig][l] * mg2[l][jg];
    }
    printf("%d ", resg[ig][jg]);
    jg++;
jmp:
     pthread_exit(NULL);

}
void mulRow(void *var)
{

    if(ig < rg1)
    {

        for ( jg=0; jg < cg2; jg++)
        {
            resg[ig][jg] = 0;
            for (l=0; l < rg2; l++)
            {
                resg[ig][jg] =resg[ig][jg] + mg1[ig][l] * mg2[l][jg];

            }
            printf("%d ", resg[ig][jg]);
        }
        ig++;
        printf("\n");
        pthread_exit(NULL);
    }
}
int main()
{
    FILE * finput;

    int i,j,r1,c1,r2,c2;
    finput = fopen("input3", "r");


    fscanf(finput, " %d %d\n", &r1, &c1);


    int m1[r1][c1];

    for(i=0; i<r1; i++)
    {

        for(j=0; j<c1; j++)
        {

            fscanf(finput, " %d\n",&m1[i][j]);

        }
    }
    for(i=0; i<r1; i++)
    {

        for(j=0; j<c1; j++)
        {

            printf("%d ",m1[i][j]);

        }
        printf("\n");
    }
    printf("\n");
    fscanf(finput, " %d %d\n", &r2, &c2);
    int m2[r2][c2];

    for(i=0; i<r2; i++)
    {

        for(j=0; j<c2; j++)
        {

            fscanf(finput, " %d\n",&m2[i][j]);
        }
    }
    for(i=0; i<r2; i++)
    {

        for(j=0; j<c2; j++)
        {

            printf("%d ",m2[i][j]);

        }
        printf("\n");
    }

    fclose(finput);



    if(c1!=r2)
    {
        printf("Matrix multiplication not possible\n");
        exit(0);
    }

    n=r1*c2;
    printf("\nNumber of Threads needed=(%d)\n\n",n);

    rg1=r1;
    cg1=c1;
    rg2=r2;
    cg2=c2;

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            mg1[i][j]=m1[i][j];
        }

    }
    for (i = 0; i < r2; i++)
    {
        for (j = 0; j < c2; j++)
        {
            mg2[i][j]=m2[i][j];
        }
    }

    pthread_t tid[n];
    printf("\nMultiplication of two matrices by element:\n\n");
    for(i=0; i<n; i++)
    {
        pthread_create(&tid[i],NULL,(void*)mulElement,NULL);
    }
        clock_gettime(CLOCK_MONOTONIC, &start);

    for(i=0; i<n; i++)
    {
        pthread_join(tid[i], NULL);
    }


    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("\n\nTime=%f nanosecond",elapsed);
    ig=0;
    jg=0;

    pthread_t tidr[rg1];
    printf("\nMultiplication of two matrices by row:\n\n");


    for(i=0; i<rg1; i++)
    {
        pthread_create(&tidr[i],NULL,(void*)mulRow,NULL);

    }

 clock_gettime(CLOCK_MONOTONIC, &start);
    for(i=0; i<rg1; i++)
    {
        pthread_join(tidr[i], NULL);

    }


    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    printf("\nTime=%f nanosecond",elapsed);

}




