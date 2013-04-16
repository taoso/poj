#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

int main()
{
    int n, i, j;
    float x, y;
    scanf("%d", &n);
    for (j = 1; j <= n; j++) {
        scanf("%f %f", &x, &y);
        for (i = 1;; i++) {
            if (100.0 * i / PI > x * x + y * y) break;
        }
        printf("Property %d: This property will begin eroding in year %d.\n",
                j, i);
    }
    printf("END OF OUTPUT.\n");

    return 0;
}
