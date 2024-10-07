#include<stdio.h>
#include<stdlib.h>
#define INT_MAX 1e9
struct process {
    int pid;    // Process ID
    int AT;     // Arrival Time
    int BT;     // Burst Time
    int ST;     // Start Time
    int CT;     // Completion Time
    int RT;     // Response Time
    int TAT;    // Turnaround Time
    int WT;     // Waiting Time
};

typedef struct process process;

int main() {
    int n;
    
    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    process p[n];
    int sum_BT = 0; // Total Burst Time
    int BT_remaining[n]; // Array to keep track of remaining burst time

    // Input arrival and burst times for each process
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;  // Process ID is assigned
        printf("Enter the arrival time and burst time for process %d: ", (i + 1));
        scanf("%d%d", &p[i].AT, &p[i].BT);
        sum_BT += p[i].BT;  // Calculate total burst time
        BT_remaining[i] = p[i].BT; // Initialize remaining burst time
    }
    
    int current_time = 0;
    int is_completed[n];
    
    // Initialize all processes as incomplete
    for(int i = 0; i < n; i++) {
        is_completed[i] = 0;
    }
    
    int completed = 0; // Track number of completed processes
    
    // While all processes are not completed
    while(completed != n) {
        int min_index = -1;
        int minimum = INT_MAX;
        
        // Find the process with the shortest remaining burst time
        for(int i = 0; i < n; i++) {
            if(p[i].AT <= current_time && is_completed[i] == 0) {
                if(BT_remaining[i] < minimum) {
                    minimum = BT_remaining[i];
                    min_index = i;
                }
                else if(BT_remaining[i] == minimum) {
                    if(p[i].AT < p[min_index].AT) {
                        min_index = i;
                    }
                }
            }
        }
        
        // If no process is ready, increment current time
        if(min_index == -1) {
            current_time++;
        } else {
            // If the process starts for the first time, set start time
            if(BT_remaining[min_index] == p[min_index].BT) {
                p[min_index].ST = current_time;
            }
            
            // Decrease the remaining burst time and increment the current time
            BT_remaining[min_index] = BT_remaining[min_index] - 1;
            current_time++;
            
            // If the process is completed
            if(BT_remaining[min_index] == 0) {
                p[min_index].CT = current_time; // Completion Time
                is_completed[min_index] = 1;    // Mark as completed
                completed++;                    // Increment completed process count
            }
        }
    }
    
    // Initialize sums for calculations
    int sum_RT = 0, sum_TAT = 0, sum_WT = 0;
    float avg_RT, avg_TAT, avg_WT;

    // Calculate RT, TAT, and WT for each process
    for(int i = 0; i < n; i++) {
        p[i].RT = p[i].ST - p[i].AT;           // Response Time
        sum_RT += p[i].RT;
        p[i].TAT = p[i].CT - p[i].AT;          // Turnaround Time
        sum_TAT += p[i].TAT;
        p[i].WT = p[i].TAT - p[i].BT;          // Waiting Time
        sum_WT += p[i].WT;
    }

    // Display process details
    printf("Process \t AT \t BT \t ST \t CT \t RT \t TAT \t WT\n");
    for(int i = 0; i < n; i++) {
        printf("%d \t\t %d \t %d \t %d \t %d \t %d \t %d \t %d\n", 
               p[i].pid, p[i].AT, p[i].BT, p[i].ST, p[i].CT, p[i].RT, p[i].TAT, p[i].WT);
    }

    // Calculate average RT, TAT, and WT
    avg_RT = (float)sum_RT / n;
    avg_TAT = (float)sum_TAT / n;
    avg_WT = (float)sum_WT / n;
    
    // CPU utilization and throughput
    float cpu_utilization = ((float)sum_BT / current_time) * 100;
    float throughput = (float)n / current_time;

    // Display averages and CPU utilization
    printf("Average Response time = %f\n", avg_RT);
    printf("Average Turnaround Time = %f\n", avg_TAT);
    printf("Average Waiting time = %f\n", avg_WT);
    printf("CPU Utilization (in percentage) = %f\n", cpu_utilization);
    printf("Throughput = %f\n", throughput);

    return 0;
}
