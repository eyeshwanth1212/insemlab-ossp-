#include <stdio.h>

int main(void)
{
    int n, a[10], b[10], r[10], c[10], f[10];
    int t = 0, done = 0, last = -1, start = 0;
    float st = 0, sw = 0, sr = 0;

    printf("Enter n, then arrival and burst times:\n");
    if (scanf("%d", &n) != 1 || n < 1 || n > 10) return 1;

    for (int i = 0; i < n; i++) {
        if (scanf("%d%d", &a[i], &b[i]) != 2 ||
            a[i] < 0 || b[i] <= 0) return 1;
        r[i] = b[i];
        f[i] = -1;
    }

    printf("Timeline (P0 = IDLE):\n");
    while (done < n) {
        int p = (last >= 0 && r[last] > 0) ? last : -1;

        for (int i = 0; i < n; i++)
            if (a[i] <= t && r[i] > 0 &&
                (p == -1 || r[i] < r[p]))
                p = i;

        if (p != last) {
            if (t > start)
                printf("%d-%d: P%d\n", start, t, last + 1);
            start = t;
            last = p;
        }

        if (p == -1) { t++; continue; }
        if (f[p] == -1) f[p] = t;

        r[p]--;
        t++;
        if (r[p] == 0) { c[p] = t; done++; }
    }
    printf("%d-%d: P%d\n", start, t, last + 1);

    printf("PID\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        int tat = c[i] - a[i];
        int wt = tat - b[i], rt = f[i] - a[i];
        printf("P%d\t%d\t%d\t%d\t%d\n",
               i + 1, c[i], tat, wt, rt);
        st += tat; sw += wt; sr += rt;
    }

    printf("Average TAT=%.2f WT=%.2f RT=%.2f\n",
           st/n, sw/n, sr/n);
    return 0;
}
