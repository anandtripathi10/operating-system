#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>
int Nproc,Nres;
int *resourse,**allocate,**maxarr,**need,*safe;
bool checksafe()
{
  int temp[Nres];
  for(int i=0;i<Nres;i++)
    temp[i]=resourse[i];
  bool finish[Nproc];
  for(int i=0;i<Nproc;i++)
    finish[i]=false;
  int Nfinish=0;
  while(Nfinish<Nproc)
  {
    bool safety=false;
    for(int i=0;i<Nproc;i++)
    {
      if(!finish[i])
      {
        bool poss=true;
        for(int j=0;j<Nres;j++)
          if(need[i][j]>temp[j])
          {
            poss=false;
            break;
          }
       if(poss)
       {
         for(int j=0;j<Nres;j++)
         {
           temp[j]+=allocate[i][j];
         }
           safe[Nfinish]=i;
           finish[i]=true;
           ++Nfinish;
           safety=true;
         
       }
      }
    }
      if(!safety)
      {
        for(int k=0;k<Nproc;k++)
          safe[k]=-1;
      }
    }
    return true;
  
}
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
  for(int i=0;i<Nres;i++)
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
  
  safe=(int*)malloc(Nproc*sizeof(*safe));
  for(int i=0; i<Nproc; i++) 
    safe[i] = -1;
  if(!checksafe())
  {
    printf("\n\tThis is unsafe State \n\t\tThe processes leads the system to a unsafe state.\n\n"); 
               exit(-1); 

  }
   for(int i=0; i<Nproc; i++) { 
               printf("    %d", safe[i]+1); 
         } 

  
  
}

