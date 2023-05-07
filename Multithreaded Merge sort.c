#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string.h>
int *garr;
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        pthread_t tid;
        pthread_t tid2;

        int m = l + (r - l) / 2;
        pthread_create(&tid,NULL,(void*)mergeSort,NULL);
        pthread_join(tid, NULL);
        mergeSort(arr, l, m);
        pthread_create(&tid2,NULL,(void*)mergeSort,NULL);
        pthread_join(tid2, NULL);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}



int main()
{
    int *inputArr;
    int i,l;
    FILE * finput;
    finput = fopen("ass", "r");
    fscanf(finput, "%d\n",&l);
    inputArr=malloc(l*sizeof(int));
    garr=malloc(l*sizeof(int));
    garr=inputArr;
    if(l==1||l==0)
    {
        printf("Already sorted\n");
        exit(0);
    }
    for(i=0; i<l; i++)
    {
        fscanf(finput, "%d\n",&inputArr[i]);
    }
    mergeSort(inputArr, 0, l - 1);
    for (i = 0; i < l; i++)
        printf("%d\n ", inputArr[i]);
    return 0;
}
