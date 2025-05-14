#include <stdio.h>
#define MAX 25

int frag[MAX], b[MAX], f[MAX];
int bf[MAX], ff[MAX]; // bf: block used flags, ff: file to block mapping
int nb, nf;

void reset() {
    for (int i = 0; i < MAX; i++) {
        bf[i] = 0;
        ff[i] = -1;
        frag[i] = 0;
    }
}

void input() {
    printf("\nEnter the number of blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of files: ");
    scanf("%d", &nf);

    printf("\nEnter the size of the blocks:\n");
    for (int i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
    }

    printf("\nEnter the size of the files:\n");
    for (int i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &f[i]);
    }
}

void display() {
    printf("\nFile No\tFile Size\tBlock No\tBlock Size\tFragment");
    for (int i = 0; i < nf; i++) {
        if (ff[i] != -1)
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i + 1, f[i], ff[i] + 1, b[ff[i]], frag[i]);
        else
            printf("\n%d\t\t%d\t\tNot Allocated", i + 1, f[i]);
    }
}

void firstFit() {
    reset();
    for (int i = 0; i < nf; i++) {
        for (int j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= f[i]) {
                ff[i] = j;
                frag[i] = b[j] - f[i];
                bf[j] = 1;
                break;
            }
        }
    }
    printf("\n\n--- First Fit Allocation ---");
    display();
}

void bestFit() {
    reset();
    int lowest;
    for (int i = 0; i < nf; i++) {
        lowest = 10000;
        for (int j = 0; j < nb; j++) {
            int temp = b[j] - f[i];
            if (bf[j] == 0 && temp >= 0 && temp < lowest) {
                ff[i] = j;
                lowest = temp;
            }
        }
        if (ff[i] != -1) {
            frag[i] = b[ff[i]] - f[i];
            bf[ff[i]] = 1;
        }
    }
    printf("\n\n--- Best Fit Allocation ---");
    display();
}

void worstFit() {
    reset();
    int highest;
    for (int i = 0; i < nf; i++) {
        highest = -1;
        for (int j = 0; j < nb; j++) {
            int temp = b[j] - f[i];
            if (bf[j] == 0 && temp >= 0 && temp > highest) {
                ff[i] = j;
                highest = temp;
            }
        }
        if (ff[i] != -1) {
            frag[i] = b[ff[i]] - f[i];
            bf[ff[i]] = 1;
        }
    }
    printf("\n\n--- Worst Fit Allocation ---");
    display();
}

int main() {
    int choice;
    input();

    firstFit();
    bestFit();
    worstFit();

    return 0;
}



/*
Enter the number of blocks: 5
Enter the number of files: 4

Enter the size of the blocks:
Block 1: 100
Block 2: 500
Block 3: 200
Block 4: 300
Block 5: 600

Enter the size of the files:
File 1: 212
File 2: 417
File 3: 112
File 4: 426


--- First Fit Allocation ---
File No File Size       Block No        Block Size      Fragment
1               212             2               500             288
2               417             5               600             183
3               112             3               200             88
4               426             Not Allocated

--- Best Fit Allocation ---
File No File Size       Block No        Block Size      Fragment
1               212             4               300             88
2               417             2               500             83
3               112             3               200             88
4               426             5               600             174

--- Worst Fit Allocation ---
File No File Size       Block No        Block Size      Fragment
1               212             5               600             388
2               417             2               500             83
3               112             4               300             188
4               426             Not Allocated

*/
