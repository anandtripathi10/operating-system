#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int Nproc,Nres;
int *resourse,**allocate,**maxarr,**need;
int main()
{
  int N,RN;
  printf("\tEnter the Number of Process : ");
  scanf("%d",&N);
  printf("\n\tEnter the Number of Resources : ");
  scanf("%d",&RN);
  Nproc=N;
  Nres=RN;
  resourse=(int *)malloc(Nproc*sizeof(resourse));
  printf("\n\t\tAvailable Resources :");
  for(int i=0;i<res;i++)
    scanf("%d ",&resourse[i]);
  allocate=(int**)malloc(Nres*sizeof(*allocate));
  for(int i=0;i<Nproc;i++)
    allocate[i]=(int *)malloc(Nres*sizeof(**allocate));
  maxarr = (int **)malloc(Nproc * sizeof(*maxarr));
        for(int i=0; i<Nproc; i++)
                maxarr[i] = (int *)malloc(Nres*sizeof(**maxarr));
  for(int i=0;i<Nproc;i++)
  {
    printf("\nEnter the resource allocated to process %d : ",i+1);
    for(int j=0;j<Nres;j++)
      scanf("%d",&allocate[i][j]);
  }
    for(int i=0;i<Nproc;i++)
    {
      printf("\nEnter the maximum required resources for the %d process : ",i+1);
      for(int j=0;j<Nres;j++)
        scanf("%d",&maxarr[i][j]);
    }
  need = (int **)malloc(Nproc * sizeof(*need));
        for(int i=0; i<Nproc; i++)
                need[i] = (int *)malloc(Nres * sizeof(**need));

        for(int i=0; i<Nproc; i++)
                for(int j=0; j<Nres; j++)
                        need[i][j] = maxarr[i][j] - allocate[i][j];

  
  
}
