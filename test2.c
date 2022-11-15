/*
 *28/06/2011: CPU-Sheduling (Shang).cpp.
 */
#include <stdio.h>
#include <stdlib.h>
 
typedef struct Process
{
    char id;
    unsigned int arrivalTime; // thoi diem den (s)
    unsigned int burstTime;   // thoi gian thuc hien (s)
} Process;
Process *queue;
int numProcess;
 
int check(int iCurrent, int time); // Ktra de ko nhap 2 process co cung thoi diem den
void FCFS(); // First Come, First Served
 
int compare(const void* a, const void* b)   // comparison function
{
    Process* arg1 = (Process*) a, *arg2 = (Process*) b;
    if( (*arg1).arrivalTime < (*arg2).arrivalTime ) return -1;
    else if( (*arg1).arrivalTime == (*arg2).arrivalTime ) return 0;
    else return 1;
}
int main()
{
 
    int i=0, time=0, kt=0, ch='A';
    printf("Nhap so tien trinh (n<20) :");
    scanf("%d",&numProcess);
 
    queue=(Process*)malloc(numProcess*sizeof(Process));
    printf("\nThoi diem tinh tu 0(s).");
    for (i=0; i<numProcess; i++)
    {
        printf("\nNhap thong tin ve tien trinh %c :",ch);
        queue[i].id=ch++;
        do
        {
            printf("\n\tNhap thoi diem den:");
            scanf("%d",&time);
            if (kt=check(i,time))
                queue[i].arrivalTime=time;
            else printf("\tThoi diem den trung voi thoi diem den cac tien trinh truoc.\n\tMoi nhap lai!");
        }while (kt==0);
        printf("\tNhap thoi gian thuc hien:");
        scanf("%d",&queue[i].burstTime);
    }
    qsort(queue, numProcess, sizeof(Process), compare);
    printf("\nSap xep cac process theo thu tu thoi diem den.");
    printf("\n+------+--------------+-------------+");
    printf("\n+  ID  + Arrival Time +  Burst Time +");
    printf("\n+------+--------------+-------------+");
 
    for (i=0; i<numProcess; i++)
    {
        printf("\n+  %c   +      %2d      +      %2d     +",queue[i].id,queue[i].arrivalTime, queue[i].burstTime);
        printf("\n+------+--------------+-------------+");
    }
    FCFS();
    system("pause");
    return 0;
}
 
int check(int iCurrent, int time)
{
    for (int i=0; i<iCurrent; i++)
        if (queue[i].arrivalTime==time) return 0;
    return 1;
}
 
void FCFS()
{
    int wait=0, time=0, waitingTime=0;
    printf("\n\nDieu phoi theo thuat toan FCFS:");
    for (int i=0; i<numProcess; i++)
    {
        wait=time-queue[i].arrivalTime;
        waitingTime+=( wait>0? wait:0 );
        if (wait<0)
        {
            printf("\n\t%3d (s)-->%3d (s) : CPU ranh.",time,queue[i].arrivalTime);
            time=queue[i].arrivalTime;
        }
        printf("\n\t%3d (s)-->%3d (s) : Tien trinh %c thuc hien.",time,time+queue[i].burstTime,queue[i].id);
        time+=queue[i].burstTime;
    }
    printf("\nThoi gian cho doi trung binh:%.2f\n",1.0*waitingTime/numProcess);
}