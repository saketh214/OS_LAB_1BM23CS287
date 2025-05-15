#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int remaining;
    int ct;
    int tat;
    int wt;
} Process;

void sortProcessesByAT(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateTimes(Process proc[], int n) {
    int finished = 0, currentTime = 0, shortest = -1, minBurst = INT_MAX;

    while (finished < n) {
        shortest = -1;
        minBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (proc[i].at <= currentTime && proc[i].remaining > 0 && proc[i].remaining < minBurst) {
                minBurst = proc[i].remaining;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        proc[shortest].remaining--;
        currentTime++;

        if (proc[shortest].remaining == 0) {
            proc[shortest].ct = currentTime;
            finished++;
        }
    }

    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].ct - proc[i].at;
        proc[i].wt = proc[i].tat - proc[i].bt;
    }
}

void printProcessDetails(Process proc[], int n) {
    int totalWT = 0, totalTAT = 0;

    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",
            proc[i].pid,
            proc[i].at,
            proc[i].bt,
            proc[i].ct,
            proc[i].tat,
            proc[i].wt);

        totalWT += proc[i].wt;
        totalTAT += proc[i].tat;
    }

    float avgWT = (float) totalWT / n;
    float avgTAT = (float) totalTAT / n;

    printf("\nAverage Waiting Time: %.2f\n", avgWT);
    printf("Average Turnaround Time: %.2f\n", avgTAT);
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
        proc[i].remaining = proc[i].bt;
    }

    sortProcessesByAT(proc, n);
    calculateTimes(proc, n);
    printProcessDetails(proc, n);

    return 0;
}
