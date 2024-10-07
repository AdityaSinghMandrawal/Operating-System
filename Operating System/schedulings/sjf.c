#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int pid;
    int AT;  // Arrival Time
    int BT;  // Burst Time
    int ST;  // Start Time
    int CT;  // Completion Time
    int RT;  // Response Time
    int TAT; // Turn Around Time
    int WT;  // Waiting Time
};

typedef struct process process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    process p[n];
    int sum_BT = 0;
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", (i + 1));
        scanf("%d%d", &p[i].AT, &p[i].BT);
        sum_BT += p[i].BT;
    }
    
    int current_time = 0;
    int is_completed[n];
    
    // Initialize the is_completed array
    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
    
    int completed = 0;
    
    while (completed != n) {
        int min_index = -1;
        int minimum = INT_MAX;
        
        // Find the process with the minimum burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].AT <= current_time && is_completed[i] == 0) {
                if (p[i].BT < minimum) {
                    minimum = p[i].BT;
                    min_index = i;
                } else if (p[i].BT == minimum) {
                    if (p[i].AT < p[min_index].AT) {
                        min_index = i;
                    }
                }
            }
        }
        
        if (min_index == -1) {
            // No process has arrived yet, increment the current time
            current_time++;
        } else {
            // Start the selected process
            p[min_index].ST = current_time;
            p[min_index].CT = p[min_index].ST + p[min_index].BT;
            current_time = p[min_index].CT;
            completed++;
            is_completed[min_index]++;
        }
    }
    
    // Calculate Response Time (RT), Turn Around Time (TAT), and Waiting Time (WT)
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
    
    // Display process details
    printf("Process \t AT \t BT \t ST \t CT \t RT \t TAT \t WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d \t %d \t %d \t %d \t %d \t %d \t %d\n",
               p[i].pid, p[i].AT, p[i].BT, p[i].ST, p[i].CT, p[i].RT, p[i].TAT, p[i].WT);
    }
    
    // Calculate and display averages
    avg_RT = (float)sum_RT / n;
    avg_TAT = (float)sum_TAT / n;
    avg_WT = (float)sum_WT / n;
    
    float cpu_utilization = ((float)sum_BT / current_time) * 100;
    float throughput = (float)n / current_time;
    
    printf("Average Response Time = %f\n", avg_RT);
    printf("Average Turn Around Time = %f\n", avg_TAT);
    printf("Average Waiting Time = %f\n", avg_WT);
    printf("CPU Utilization (in percentage) = %f\n", cpu_utilization);
    printf("Throughput = %f\n", throughput);
}
