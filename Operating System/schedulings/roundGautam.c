#include<stdio.h>
#include<stdlib.h>

struct process {
    int pid;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int st;  // Start Time
    int ct;  // Completion Time
    int rt;  // Response Time
    int tat; // Turn Around Time
    int wt;  // Waiting Time
    int remaining_time; // Remaining Burst Time
};

typedef struct process process;

int findmax(int a, int b) {
    return a > b ? a : b;
}

int comp(const void* a, const void* b) {
    process* p1 = (process*)a;
    process* p2 = (process*)b;
    return p1->at - p2->at; // Compare by Arrival Time
}

int comp1(const void* a, const void* b) {
    process* p1 = (process*)a;
    process* p2 = (process*)b;
    return p1->pid - p2->pid; // Compare by Process ID
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    process p[n];
    int sum_BT = 0; // Sum of Burst Times
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", (i + 1));
        scanf("%d%d", &p[i].at, &p[i].bt);
        sum_BT += p[i].bt;
        p[i].remaining_time = p[i].bt;
    }
    
    printf("Enter the time quantum: ");
    int tq;
    scanf("%d", &tq);
    
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;
    
    int queue[100];
    int front = -1, rear = -1;
    
    qsort(p, n, sizeof(process), comp); // Sort by arrival time
    
    front = rear = 0;
    queue[rear] = 0;
    visited[0] = 1;
    
    int completed = 0;
    int current_time = 0;
    
    while (completed != n) {
        int index = queue[front];
        front++;
        
        if (p[index].remaining_time == p[index].bt) {
            p[index].st = findmax(current_time, p[index].at);
            current_time = p[index].st;
        }
        
        if (p[index].remaining_time - tq > 0) {
            current_time += tq;
            p[index].remaining_time -= tq;
        } else {
            current_time += p[index].remaining_time;
            p[index].remaining_time = 0;
            completed++;
            p[index].ct = current_time;
        }
        
        for (int i = 1; i < n; i++) {
            if (p[i].remaining_time > 0 && p[i].at <= current_time && visited[i] == 0) {
                rear++;
                queue[rear] = i;
                visited[i] = 1;
            }
        }
        
        if (p[index].remaining_time > 0) {
            queue[++rear] = index;
        }
        
        if (front > rear) {
            for (int i = 1; i < n; i++) {
                if (p[i].remaining_time > 0) {
                    queue[++rear] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }
    
    int sum_RT = 0, sum_TAT = 0, sum_WT = 0;
    float avg_RT, avg_TAT, avg_WT;
    
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].st - p[i].at; // Response Time
        sum_RT += p[i].rt;
        p[i].tat = p[i].ct - p[i].at; // Turnaround Time
        sum_TAT += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt; // Waiting Time
        sum_WT += p[i].wt;
    }
    
    qsort(p, n, sizeof(process), comp1); // Sort by process ID for output
    
    printf("Process\t AT\t BT\t ST\t CT\t RT\t TAT\t WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].rt, p[i].tat, p[i].wt);
    }
    
    avg_RT = (float)sum_RT / n;
    avg_TAT = (float)sum_TAT / n;
    avg_WT = (float)sum_WT / n;
    
    float cpu_utilization = ((float)sum_BT / current_time) * 100;
    float throughput = (float)n / current_time;
    
    printf("Average Response Time = %.2f\n", avg_RT);
    printf("Average Turnaround Time = %.2f\n", avg_TAT);
    printf("Average Waiting Time = %.2f\n", avg_WT);
    printf("CPU Utilization = %.2f%%\n", cpu_utilization);
    printf("Throughput = %.2f\n", throughput);
    
    return 0;
}
