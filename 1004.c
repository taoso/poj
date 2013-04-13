#include <stdio.h>

int main()
{
    int n = 12;
    double m = 0;
    double tm = 0;
    for (; n > 0; n--) {
        scanf("%lf", &m);
        tm += m;
    }
    printf("$%.2lf\n", tm / 12.0);
    return 0;
}
