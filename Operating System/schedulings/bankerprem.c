#include<stdio.h>
int main() {
    int n, r;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &r);
    int alloc[n][r],maxalloc[n][r],ava[r],total[r];  
    for (int i = 0; i < r; i++) {
        ava[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter the allocated resources for process %d: ", i + 1);
        for (int j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
        printf("Enter the maximum allocated resources for process %d: ", i + 1);
        for (int j = 0; j < r; j++) {
            scanf("%d", &maxalloc[i][j]);
        }
    }
    printf("Enter the total resources available in the system: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &total[i]);
    }
    for (int i = 0; i < r; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += alloc[j][i];  
        }
        ava[i] = total[i] - sum;
    }
    int need[n][r];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = maxalloc[i][j] - alloc[i][j];
        }
    }
    int f[n], ss[n], ind = 0;
    for (int k = 0; k < n; k++) {
        f[k] = 0; 
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {  
                int flag = 0;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > ava[j]) {  
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ss[ind++] = i;  
                    for (int y = 0; y < r; y++) {
                        ava[y] += alloc[i][y]; 
                    }
                    f[i] = 1; 
                }
            }
        }
    }
    printf("\nSafe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", ss[i]+1);
    }
//24351
    return 0;
}
#include<stdio.h>

int main() {
    int n, r;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &r);
    
    int alloc[n][r], maxalloc[n][r], ava[r], total[r];  
    
    // Initialize available resources to 0
    for (int i = 0; i < r; i++) {
        ava[i] = 0;
    }
    
    // Input allocated and maximum resources for each process
    for (int i = 0; i < n; i++) {
        printf("Enter the allocated resources for process %d: ", i + 1);
        for (int j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
        printf("Enter the maximum allocated resources for process %d: ", i + 1);
        for (int j = 0; j < r; j++) {
            scanf("%d", &maxalloc[i][j]);
        }
    }
    
    // Input total available resources in the system
    printf("Enter the total resources available in the system: ");
    for (int i = 0; i < r; i++) {
        scanf("%d", &total[i]);
    }
    
    // Calculate available resources
    for (int i = 0; i < r; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += alloc[j][i];  
        }
        ava[i] = total[i] - sum;
    }
    
    // Calculate the need matrix
    int need[n][r];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = maxalloc[i][j] - alloc[i][j];
        }
    }
    
    int f[n], ss[n], ind = 0; // flags and safe sequence
    for (int k = 0; k < n; k++) {
        f[k] = 0; // All processes initially not finished
    }
    
    for (int k = 0; k < n; k++) {
        int max_release_index = -1;
        int max_resources_freed = -1;

        // Loop through all processes to find the one that frees the maximum resources
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {  // If the process is not finished
                int flag = 0;
                
                // Check if the process can be executed
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > ava[j]) {  
                        flag = 1;
                        break;
                    }
                }

                // If the process can be executed, calculate total resources it will free
                if (flag == 0) {
                    int resources_freed = 0;
                    for (int j = 0; j < r; j++) {
                        resources_freed += alloc[i][j];
                    }

                    // Check if this process frees more resources than the current maximum
                    if (resources_freed > max_resources_freed) {
                        max_resources_freed = resources_freed;
                        max_release_index = i;
                    }
                }
            }
        }

        // If no process could be executed, there is an error
        if (max_release_index == -1) {
            printf("System is in unsafe state!\n");
            return -1;
        }

        // Execute the process that frees the maximum resources
        ss[ind++] = max_release_index;

        // Release the resources
        for (int y = 0; y < r; y++) {
            ava[y] += alloc[max_release_index][y]; 
        }

        f[max_release_index] = 1;  // Mark process as finished
    }

    // Output the safe sequence
    printf("\nSafe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d -> ", ss[i] + 1);
    }
    printf("done\n");

    return 0;
}
