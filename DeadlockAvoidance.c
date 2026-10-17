#include <stdio.h>

int n, m, a[10][10], mx[10][10], need[10][10];
int avail[10], finish[10], seq[10], count = 0;

void safe(int work[], int len)
{
    if (len == n) {
        count++;
        printf("Safe sequence %d: ", count);

        for (int i = 0; i < n; i++)
            printf("T%d ", seq[i]);

        printf("\n");
        return;
    }

    int found = 0;

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            int ok = 1;

            for (int j = 0; j < m; j++)
                if (need[i][j] > work[j])
                    ok = 0;

            if (ok) {
                found = 1;
                int w[10];

                /* Resources available after tenant finishes */
                for (int j = 0; j < m; j++)
                    w[j] = work[j] + a[i][j];

                finish[i] = 1;
                seq[len] = i;

                safe(w, len + 1);

                /* Backtrack to explore other sequences */
                finish[i] = 0;
            }
        }
    }

    /* No unfinished tenant can complete */
    if (!found) {
        printf("\nBlocked prefix: ");

        if (len == 0)
            printf("(none completed)");

        for (int i = 0; i < len; i++)
            printf("T%d ", seq[i]);

        printf("\nWaiting tenants: ");
        for (int i = 0; i < n; i++)
            if (!finish[i])
                printf("T%d ", i);

        printf("\nAvailable resources: ");
        for (int j = 0; j < m; j++)
            printf("%d ", work[j]);

        printf("\n");
    }
}

int main(void)
{
    printf("Enter tenants and resources: ");
    if (scanf("%d%d", &n, &m) != 2 ||
        n < 1 || n > 10 || m < 1 || m > 10)
        return 1;

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (scanf("%d", &a[i][j]) != 1 || a[i][j] < 0)
                return 1;

    printf("Enter Maximum matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &mx[i][j]) != 1 ||
                mx[i][j] < a[i][j])
                return 1;

            need[i][j] = mx[i][j] - a[i][j];
        }
    }

    printf("Enter Available resources:\n");
    for (int j = 0; j < m; j++)
        if (scanf("%d", &avail[j]) != 1 || avail[j] < 0)
            return 1;

    safe(avail, 0);

    if (count > 0)
        printf("\nSystem is SAFE. Total sequences: %d\n", count);
    else
        printf("\nSystem is UNSAFE. No safe sequence exists.\n");

    return 0;
}
