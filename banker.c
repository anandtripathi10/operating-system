#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>
#include<time.h>
int Nproc,Nres,ProcComplete=0;
int *resourse,**allocate,**maxarr,**need,*safe;
pthread_mutex_t lockResources;
pthread_cond_t condition;
void *ProcessExe(void *arg)
{
  int p=*((int *)arg);
  pthread_mutex_lock(&lockResources);
  while(p!=safe[ProcComplete])
    pthread_cond_wait(&condition,&lockResources);
  printf("\n\n========  Process no : %d   ========>",p+1);
  printf("    Allocated Resources: ");
  for(int i=0;i<Nres;i++)
  {
    printf("  %d",allocate[p][i]);
          
  }
    printf("\n\t\t\t\t\tResourses needed:  ");
           
    for(int i=0; i<Nres; i++) 
       printf(" %d", need[p][i]); 
     
     printf("\n\t\t\t\t\tNow Available  Resources are : "); 
     for(int i=0; i<Nres; i++) 
           printf(" %d", resourse[i]); 
     printf("\n");
           sleep(1);
           printf("\n\t\t\t\t\tResourses are Allocated: ");
           sleep(1);
           printf("\n\t\t\t\t\tProcess is Executing : ");
           sleep(rand()%3+2);
           printf("\n\t\t\t\t\tProcess Executed: ");
           sleep(1);
           printf("\n\t\t\t\t\tProcess Releasing the Resources:");
           sleep(1);
           printf("\n\t\t\t\t\tResources are released : ");
           for(int i=0;i<Nres;i++)
           resourse[i]+=allocate[p][i];
           printf("\n\tNow Available : ");
           for(int i=0;i<Nres;i++)
           printf(" %d",resourse[i]);
           sleep(1);
           ProcComplete++;
           
           pthread_cond_broadcast(&condition);
           pthread_mutex_unlock(&lockResources);
           pthread_exit(NULL);
           

         
}

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
        { safe[k]=-1;} return false;
      }
    }
    return true;
  
}
int main()
{
  //taking input of Number of process and Resources
  int N,RN;
  printf("\tEnter the Number of Process : ");
  scanf("%d",&N);
  printf("\n\tEnter the Number of Resources : ");
  scanf("%d",&RN);
  Nproc=N;
  Nres=RN;
  //declaring datastructure used in banker's Algorithm
  resourse=(int *)malloc(Nres*sizeof(resourse));
  printf("\n\t\tAvailable Resources :");
  for(int i=0;i<Nres;i++)
    scanf("%d",&resourse[i]);
  allocate=(int**)malloc(Nproc*sizeof(*allocate));
  for(int i=0;i<Nproc;i++)
    allocate[i]=(int *)malloc(Nres*sizeof(**allocate));
  maxarr = (int **)malloc(Nproc * sizeof(*maxarr));
        for(int i=0; i<Nproc; i++)
                maxarr[i] = (int *)malloc(Nres*sizeof(**maxarr));
  printf("\n++++++++++++++++++  Allocated Resources  +++++++++++++++");
  
  for(int i=0;i<Nproc;i++)
  {
    printf("\nEnter the resource allocated to process %d : ",i+1);
    for(int j=0;j<Nres;j++)
      scanf("%d",&allocate[i][j]);
  }
  printf("\n++++++++++++++++++  Required resource  ++++++++++++++++++");
  
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
  //Checking for Safe sequence 
  if(!checksafe())
  {
    printf("\n\tThis is unsafe State \n\t\tThe processes leads the system to a unsafe state.\n\n"); 
               exit(-1); 

  }
  printf("\n------------->Safe sequence is:  ");
   for(int i=0; i<Nproc; i++) { 
     printf("    %d", safe[i]+1); 
         } 
    printf("\n\n\t\t\t\t\t\t=====  Execution Starts  ========\n");

//Implementing Banker algorithm using Multithreaded Program
  pthread_t process[Nproc];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  int processNum[Nproc];
  for(int i=0;i<Nproc;i++)
    processNum[i]=i;
  for(int i=0;i<Nproc;i++)
    pthread_create(&process[i],&attr,ProcessExe,(void*)(&processNum[i]));
  for(int i=0;i<Nproc;i++)
    pthread_join(process[i],NULL);
  printf("\n\n\t____________________________Task completed_____________________");
}
