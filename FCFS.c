//FCFS
#include<stdio.h>
 
int main()
{
    int n,bt[20],wt[20],tat[20],avgwt=0,avgtat=0,i,j;
    printf("Enter total number of processes(maximum 20):");
    scanf("%d",&n);
 
    printf("\nEnter Process Burst Time\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&bt[i]);
    }
 
    wt[0]=0;    //considering waiting time for process 1 as 0 
 
     for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
 //considering arrival time as same and waiting time for each process is calculated in the above
 
    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");
 

    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];
        avgwt+=wt[i];
        avgtat+=tat[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,bt[i],wt[i],tat[i]);
    }
 
    avgwt/=i;
    avgtat/=i;

    printf("\n\nAverage Waiting Time:%d",avgwt);
    printf("\nAverage Turnaround Time:%d",avgtat);
 
    return 0;
}
