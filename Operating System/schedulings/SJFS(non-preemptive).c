#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int st;
    int ct;
    float rt;
    float tat;
    float wt;
};
int main()
{
    int n;
    printf("Enter the number of processes.\n");
    scanf("%d",&n);
    struct Process p[n];
    bool isCompleted[100] = {false};
    float sumWT = 0.0, sumTAT = 0.0, sumRT = 0.0, CPU = 0.0;
    printf("Enter the arrival time and burst time of the processes.\n");
    for( int i = 0; i<n; i++ )
    {
        printf("For process %d, enter arrival time and burst time.\n",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].pid = i+1;
    }

    int completed = 0, currentTime = 0;
    int freeTime = 0;
    while( completed != n )
    {
        int min_index = -1;
        int minBurstTime = INT_MAX;
        for( int i = 0; i<n; i++ )
        {
            if( p[i].at <= currentTime && isCompleted[i] == false )
            {
                if( p[i].bt < minBurstTime )
                {
                    minBurstTime = p[i].bt;
                    min_index = i;
                }
            }
            if( p[i].bt == minBurstTime )       //if two process of same burst time will collide then take that process whose at is minimum.
            {
                if( p[i].at < p[min_index].at )
                {
                    min_index = i;
                }
            }
        }

        if( min_index == -1 )
        {
            currentTime++;
            freeTime++;
        }
        else
        {
            p[min_index].st = currentTime;
            p[min_index].ct = p[min_index].st + p[min_index].bt;
            p[min_index].rt = p[min_index].st - p[min_index].at;
            p[min_index].tat = p[min_index].ct - p[min_index].at;
            p[min_index].wt = p[min_index].tat - p[min_index].bt;

            sumRT += p[min_index].rt;
            sumTAT += p[min_index].tat;
            sumWT += p[min_index].wt;
            completed++;
            isCompleted[min_index] = true;
            currentTime = p[min_index].ct;
        }
    }

    printf("\nPID\tAT\tBT\tST\tCT\tRT\tTAT\tWT\n");
    for( int i = 0; i<n; i++ )
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].rt,p[i].tat,p[i].wt);
    }
    float length_cycle = p[n-1].ct - p[0].at;
    printf("Total Response Time = %f\n",sumRT);
    printf("Average Response Time = %f\n",sumRT/n);
    printf("Total Turn Around Time = %f\n",sumTAT);
    printf("Average Turn Around Time = %f\n",sumTAT/n);
    printf("Total Waiting Time = %f\n",sumWT);
    printf("Average Waiting Time = %f\n",sumWT/n);
    printf("Throughput = %f\n",n/length_cycle);
    printf("CPU% = %f\n",(length_cycle - freeTime)/length_cycle * 100);

    printf("\n------------------------------------------------------------------------------------------------\n");
    printf("Name: Sourav Bisht\t Section: A2\t Roll No: 65\n");
    return 0;
}
