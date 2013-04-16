#include <stdio.h>

int main()
{
    int p, e, i, d;
    int j,k;
    j = 0;
    scanf("%d %d %d %d", &p, &e, &i, &d);
    while (p != -1 && e != -1 && i != -1 && d != -1) {
        for (k = d + 1; k <= 21252 + d; k++) {
            if ((k - p) % 23 == 0
                    && (k - e) % 28 == 0
                    && (k - i) % 33 == 0)
                break;
        }
        printf("Case %d: the next triple peak occurs in %d days.\n", ++j,
                (k <= 21252) ? k-21252 : 25252);
        scanf("%d %d %d %d", &p, &e, &i, &d);
    }
    return 0;
}
