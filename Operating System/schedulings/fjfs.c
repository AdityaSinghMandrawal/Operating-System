#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int AT;   // Arrival Time
    int BT;   // Burst Time
    int ST;   // Start Time
    int CT;   // Completion Time
    int RT;   // Response Time
    int TAT;  // Turnaround Time
    int WT;   // Waiting Time
};
typedef struct process process;

int comp(const void *a, const void *b) {
    process* p1 = (process*)a;
    process* p2 = (process*)b;
    if (p1->AT != p2->AT)
        return p1->AT - p2->AT;
    else
        return p1->pid - p2->pid;  // Secondary sort by PID
}


int comp1(const void* a, const void* b) {
    process* p1 = (process*)a;
    process* p2 = (process*)b;
    return p1->pid - p2->pid;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    process p[n];
    int sum_BT = 0;
    
    // Input the processes
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", (i + 1));
        scanf("%d %d", &p[i].AT, &p[i].BT);
        sum_BT += p[i].BT;
    }

    // Sort based on arrival time
    qsort(p, n, sizeof(process), comp);
    
    int current_time = 0;
    
    // Process each process
    for (int i = 0; i < n; i++) {
        if (p[i].AT <= current_time) {
            p[i].ST = current_time;
            p[i].CT = p[i].ST + p[i].BT;
            current_time += p[i].BT;
        } else {
            current_time = p[i].AT;
            p[i].ST = current_time;
            p[i].CT = p[i].ST + p[i].BT;
            current_time += p[i].BT;
        }
    }

    // Calculate RT, TAT, WT
    int sum_RT = 0, sum_TAT = 0, sum_WT = 0;
    float avg_RT, avg_TAT, avg_WT;
    
    for (int i = 0; i < n; i++) {
        p[i].RT = p[i].ST - p[i].AT;
        sum_RT += p[i].RT;
        
        p[i].TAT = p[i].CT - p[i].AT;
        sum_TAT += p[i].TAT;
        
        p[i].WT = p[i].TAT - p[i].BT;
        sum_WT += p[i].WT;
    }

    // Sort back based on process ID
    qsort(p, n, sizeof(process), comp1);

    // Print the result table
    printf("\nProcess\tAT\tBT\tST\tCT\tRT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].ST, p[i].CT, p[i].RT, p[i].TAT, p[i].WT);
    }

    // Calculate averages
    avg_RT = (float)sum_RT / n;
    avg_TAT = (float)sum_TAT / n;
    avg_WT = (float)sum_WT / n;
    
    float cpu_utilization = ((float)sum_BT / current_time) * 100;
    float throughput = (float)n / current_time;

    // Print the results
    printf("\nAverage Response Time = %.2f\n", avg_RT);
    printf("Average Turn Around Time = %.2f\n", avg_TAT);
    printf("Average Waiting Time = %.2f\n", avg_WT);
    printf("CPU Utilization (in percentage) = %.2f%%\n", cpu_utilization);
    printf("Throughput = %.2f processes/unit time\n", throughput);

    return 0;
}
