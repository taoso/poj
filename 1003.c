#include <stdio.h>

int get_cards(float l)
{
    int i = 1;
    float c = 0;
    while (c < l) {
        c += 1.0 / (i + 1);
        i++;
    }
    return i - 1;
}

int main()
{
    float l;
    scanf("%f", &l);
    while (l > 0.00) {
        printf("%d card(s)\n", get_cards(l));
        scanf("%f", &l);
    }

    return 0;
}
