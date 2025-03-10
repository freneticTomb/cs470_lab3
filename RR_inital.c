#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;



// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = proc[i].burst_time;
    }

    int current_time = 0;
    
    printf("Execution Order: ");

    // Keep traversing processes in round-robin manner until all of them are not done
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            // If burst time of a process is greater than 0 then only need to process further
            if (remaining_time[i] > 0) {
                done = 0;
                
                // Execute for time quantum
                if (remaining_time[i] > quantum) {
                    printf("P%d ", proc[i].process_id);
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                } 
                else {
                    // Execute for remaining time
                    printf("P%d ", proc[i].process_id);
                    current_time += remaining_time[i];
                    proc[i].waiting_time = current_time - proc[i].burst_time - proc[i].arrival_time;
                    
                    remaining_time[i] = 0;
                }
            }
        }
        // If all processes are done
        if (done == 1) break;
    }
    printf("\n");
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}
