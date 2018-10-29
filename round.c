//conventional rr
#include<stdio.h> 
 
int main() 
{ 
 
  int count,j,n,time,remain,flag=0,time_quantum; 
  int wait_time=0,turnaround_time=0, at[10],bt[10],rt[10]; 
  printf("Enter Total Process:\t "); 
  scanf("%d",&n); 
  remain=n; 
  for(count=0;count<n;count++) 
  { 
    printf("Enter Burst Time for Process Process Number %d :",count+1); 
    at[count] = 0;
    scanf("%d",&bt[count]); 
    rt[count]=bt[count]; 
  } 
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&time_quantum); 
  printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n"); 
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=time_quantum && rt[count]>0) 
    { 
      time+=rt[count]; 
      rt[count]=0; 
      flag=1; 
    } 
	// in the next conditional statement, rt>time_quantum
    else if(rt[count]>0) 
    { 
      rt[count]-=time_quantum; 
      time+=time_quantum; 
    } 
    if(rt[count]==0 && flag==1) 
    { 
      remain--; 
	// Process\t|Turnaround Time=time-at |Waiting Time=  time-at-bt
      printf("P[%d]\t|\t%d\t|\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
      wait_time+=time-at[count]-bt[count]; 
      turnaround_time+=time-at[count]; 
	// updating wait time and turn around time for next process
      flag=0; 
    } 
    if(count==n-1) 
      count=0; // if reached last then goto first process again
    else if(at[count+1]<=time) 
      count++;  
    else 
      count=0; //otherwise start with first
  } 
  printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Average Turnaround Time = %f",turnaround_time*1.0/n);

  
  return 0; 
}
