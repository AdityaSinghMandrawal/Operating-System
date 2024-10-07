#include<stdio.h>
#include<stdlib.h>

struct process {
    int pid;      
    int AT;        
    int BT;       
    int ST;        
    int CT;        
    int RT;        
    int TAT;       
    int WT;        
    int priority; 
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
        printf("Enter the arrival time, burst time and priority for process %d: ", (i + 1));
        scanf("%d%d%d", &p[i].AT, &p[i].BT, &p[i].priority);
        sum_BT += p[i].BT;
    }

    int current_time = 0;
    int is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = 0;

    int completed = 0;
    while (completed != n) {
        int max_index = -1;
        int maximum = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].AT <= current_time && is_completed[i] == 0) {
                if (p[i].priority > maximum) {
                    maximum = p[i].priority;
                    max_index = i;
                } else if (p[i].priority == maximum) {
                    if (p[i].AT < p[max_index].AT) {
                        max_index = i;
                    }
                }
            }
        }

        if (max_index == -1) {
            current_time++;
        } else {
            p[max_index].ST = current_time;
            p[max_index].CT = p[max_index].ST + p[max_index].BT;
            current_time += p[max_index].BT;
            completed++;
            is_completed[max_index] = 1;
        }
    }

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

    printf("Process \t AT \t BT \t Priority \t ST \t CT \t RT \t TAT \t WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d \t %d \t %d \t\t %d \t %d \t %d \t %d \t %d\n", 
               p[i].pid, p[i].AT, p[i].BT, p[i].priority, p[i].ST, p[i].CT, 
               p[i].RT, p[i].TAT, p[i].WT);
    }

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

    return 0;
}
