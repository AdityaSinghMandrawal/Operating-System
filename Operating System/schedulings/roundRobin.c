#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int r_bt;
    int st;
    int ct;
    float rt;
    float tat;
    float wt;
};

int findMax( int a, int b)
{
    return a>b ? a : b;
}

int compareAT(const void *p1, const void *p2)       //sort acc. to arrival time if arrival time is same then sort acc. to pid.
{
    int a = ((struct Process*)p1)->at;
    int b = ((struct Process*)p2)->at;
    if( a<b )
        return -1;
    else if( a>b )
        return 1;
    else{
        int p = ((struct Process*)p1)->pid;
        int q = ((struct Process*)p2)->pid;
        if( p<q )
            return -1;
        else
            return 1;
    }
}

int comparePID(const void *p1,const void *p2)       //sort acc. to pid, used in last to make output in the same manner as of input.
{
    int a = ((struct Process*)p1)->pid;
    int b = ((struct Process*)p2)->pid;
    if( a<b )
        return -1;
    else
        return 1;
}

int main()
{
    int n;
    printf("Enter the number of processes.\n");
    scanf("%d",&n);
    struct Process p[n];
    bool isVisited[1000] = {false};
    int tq = 0;
    float sumWT = 0.0, sumTAT = 0.0, sumRT = 0.0, sumBT = 0.0;
    int completed = 0, currentTime = 0;
    int total_idle_time = 0;
    bool isFirstProcess = true;
    int queue[10000];
    int front = -1, rear = -1, index = -1;

    printf("Enter the arrival time and burst time of the processes.\n");
    for( int i = 0; i<n; i++ )
    {
        printf("For process %d, enter arrival time and burst time.\n",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i].pid = i;
        p[i].r_bt = p[i].bt;            // remaining burst time would be equal to burst time of a process in the start
    }

    printf("Enter the time quantum.\n");
    scanf("%d",&tq);

    qsort((void*)p,n,sizeof(struct Process),compareAT);     // round robin starts from here.

    front = rear = 0;       //enter the first process in the queue;
    queue[0] = 0;
    isVisited[0] = true;

    while( completed != n )
    {
        index = queue[front];
        front++;

        if( p[index].r_bt == p[index].bt )          //this means, the process is executing for the first time;
        {
            p[index].st = findMax(currentTime,p[index].at);
            currentTime = p[index].st;
            total_idle_time += (isFirstProcess == true ) ? 0 : p[index].st - currentTime;
            isFirstProcess = false;
        }

        if( p[index].r_bt - tq > 0 )        //process is executing as of time quantum.
        {
            p[index].r_bt -= tq;
            currentTime += tq;
        }
        else                // if the process got fully executed.
        {
            currentTime += p[index].r_bt;
            p[index].r_bt = 0;
            p[index].ct = currentTime;
            p[index].rt = p[index].st - p[index].at;
            p[index].tat = p[index].ct - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;

            completed++;
            sumWT += p[index].wt;
            sumRT += p[index].rt;
            sumTAT += p[index].tat;
            sumBT += p[index].bt;
        }

        for( int i = 1; i<n; i++ )
        {
            if( p[i].r_bt > 0 && p[i].at <= currentTime && isVisited[i] == false )
            {
                ++rear;
                queue[rear] = i;
                isVisited[i] = true;
            }
        }

        if( p[index].r_bt > 0 )
        {
            ++rear;
            queue[rear] = index;
        }

        if( front > rear )
        {
            for( int i = 1; i<n; i++ )
            {
                if( p[i].r_bt > 0 )
                {
                    ++rear;
                    queue[rear] = i;
                    isVisited[i] = true;
                    break;
                }
            }
        }
    }                   //end of round robin.

    int maxCompletionTime = INT_MIN;
    int minStartTime = INT_MAX;
    for( int i = 0; i<n; i++ )
    {
        if( p[i].ct > maxCompletionTime )
            maxCompletionTime  = p[i].ct;
        if( p[i].st < minStartTime )
            minStartTime = p[i].st;
    }
    int total_time_length = maxCompletionTime - minStartTime;

    qsort((void*)p,n,sizeof(struct Process),comparePID);
    printf("\nPID\tAT\tBT\tST\tCT\tRT\tTAT\tWT\n");
    for( int i = 0; i<n; i++ )
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",p[i].pid,p[i].at,p[i].bt,p[i].st,p[i].ct,p[i].rt,p[i].tat,p[i].wt);
    }

    printf("Total Waiting Time = %.2f\n",sumWT);
    printf("Average Waiting Time = %.2f\n",sumWT/n);
    printf("Total Turn Around Time = %.2f\n",sumTAT);
    printf("Average Turn Around Time = %.2f\n",sumTAT/n);
    printf("Throughput = %.2f\n",(float)n/total_time_length);
    printf("CPU% = %.2f\n",(float)sumBT/total_time_length * 100);

    printf("\n--------------------------------------------------------------------------------------\n");
    printf("Name:- Sourav Bisht\t Section:-A2\t Roll No:- 65\n");

    return 0;
}
