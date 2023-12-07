#include <stdio.h>
int curr[5][5], maxclaim[5][5], avl[5];
int alloc[5] = {0, 0, 0, 0, 0};
int maxres[5], running[5], safe = 0;
int count = 0, i, j, exec, r, p, k = 1;
int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &p);
    for (i = 0; i < p; i++) {
        running[i] = 1;
        count++;
    }
    printf("Enter the number of resources: ");
    scanf("%d", &r);
    for (i = 0; i < r; i++) {
        printf("Enter the resource for instance %d: ", k++);
        scanf("%d", &maxres[i]);
    }
    printf("Enter maximum resource table:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &maxclaim[i][j]);
        }
    }
    printf("Enter allocated resource table:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &curr[i][j]);
        }
    }
    printf("The resource of instances: ");
    for (i = 0; i < r; i++) {
        printf("%d\t", maxres[i]);
    }
    printf("\n");
    printf("The allocated resource table:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            printf("%d\t", curr[i][j]);
        }
        printf("\n");
    }
    printf("The maximum resource table:\n");
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            printf("%d\t", maxclaim[i][j]);
        }
        printf("\n");
    }
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            alloc[j] += curr[i][j];
        }
    }
    printf("Allocated resources:\t");
    for (i = 0; i < r; i++) {
        printf("%d\t", alloc[i]);
    }
    for (i = 0; i < r; i++) {
        avl[i] = maxres[i] - alloc[i];
    }
    printf("\nAvailable resources:\t");
    for (i = 0; i < r; i++) {
        printf("%d\t", avl[i]);
    }
    printf("\n");
    // Main procedure goes below to check for an unsafe state.
    while (count != 0) {
        safe = 0;
        for (i = 0; i < p; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < r; j++) {
                    if (maxclaim[i][j] - curr[i][j] > avl[j]) {
                        exec = 0;
                        break;
                    }
                }
                if (exec) {
                    printf("\nProcess %d is executing\n", i + 1);
                    running[i] = 0;
                    count--;
                    safe = 1;
                    for (j = 0; j < r; j++) {
                        avl[j] += curr[i][j];
                    }
                    break;
                }
            }
        }
        if (!safe) {
            printf("\nThe processes are in an unsafe state.\n");
            break;
        } else {
            printf("\nThe process is in a safe state.\n");
            printf("Safe sequence is:");
            for (i = 0; i < p; i++) {
                printf("%d\t", avl[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
