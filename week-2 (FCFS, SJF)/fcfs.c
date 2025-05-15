#include <stdio.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
} Process;

void sortProcessesByAT(Process proc[], int n) {
   
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}
void calculateTimes(Process proc[], int n) {
    proc[0].ct = proc[0].at + proc[0].bt;
    proc[0].tat = proc[0].ct - proc[0].at;
    proc[0].wt = proc[0].tat - proc[0].bt;

    for (int i = 1; i < n; i++) {
       
        proc[i].ct = proc[i-1].ct + proc[i].bt;
   
        proc[i].tat = proc[i].ct - proc[i].at;
       
        proc[i].wt = proc[i].tat - proc[i].bt;
    }
}
void printProcessDetails(Process proc[], int n) {
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        // Print the processes as P1, P2, P3...
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",
            proc[i].pid,  // Print PID as P1, P2, P3... based on index
            proc[i].at,
            proc[i].bt,
            proc[i].ct,
            proc[i].tat,
            proc[i].wt);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
   
    Process proc[n];

   
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;  
        printf("Enter Arrival Time (AT) for P%d: ", i + 1);
        scanf("%d", &proc[i].at);
        printf("Enter Burst Time (BT) for P%d: ", i + 1);
        scanf("%d", &proc[i].bt);
    }

   
    sortProcessesByAT(proc, n);

   
    calculateTimes(proc, n);

   
    printProcessDetails(proc, n);

    return 0;
}
