#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strstrip_zero(char *s)
{
    size_t size;
    char *end;
    int has_dot = 0;

    size = strlen(s);

    if (!size) return s;

    end = s + size - 1;
    while (end >= s) {
        if (*end == '.') {
            has_dot = 1;
            break;
        }
        end--;
    }

    if (has_dot) {
        end = s + size - 1;
        while (end >= s && *end == '0') end--;

        if (*end != '.') {
            *(end + 1) = '\0';
        } else {
            *end = '\0';
        }
    }


    while (*s && *s == '0') s++;

    return s;
}

char *multiply(char* a, char *b)
{
    int round = 0;
    int a_dot = -1, b_dot = -1;
    int a_len = 0, b_len = 0;
    int i,j;
    char *p;
    int *q;

    p = a;
    while (*p) {
        if (*p == '.') {
            a_dot = (p - a);
            break;
        }
        p++;
    }
    p = b;
    while (*p) {
        if (*p == '.') {
            b_dot = (p - b);
            break;
        }
        p++;
    }
    a_len = strlen(a) - (a_dot == -1 ? 0 : 1);
    b_len = strlen(b) - (b_dot == -1 ? 0 : 1);

    int dot_len = (a_dot == -1 ? 0 : (a_len - a_dot)) \
                  + (b_dot == -1 ? 0 : (b_len - b_dot));

    int *a_int = (int *) calloc(a_len, sizeof(int));
    int *b_int = (int *) calloc(b_len, sizeof(int));

    p = a;
    q = a_int;
    while (*p) {
        if (*p != '.') {
            *q = *p - '0';
            q++;
        }
        p++;
    }
    p = b;
    q = b_int;
    while (*p) {
        if (*p != '.') {
            *q = *p - '0';
            q++;
        }
        p++;
    }

    int **m = (int **) malloc(b_len * sizeof(int *));
    m[0] = (int *) calloc((a_len + b_len) * b_len, sizeof(int));
    for (i = 1; i < b_len; i++)
        m[i] = m[i - 1] + a_len + b_len;

    for (i = b_len - 1; i >= 0; i--) {
        round = 0;
        for (j = a_len - 1; j >= 0; j--) {
            int tmp = (b_int[i] * a_int[j]) + round;
            round = tmp / 10;
            tmp = tmp % 10;
            m[i][i + j + 1] = tmp;
        }
        m[i][i + j + 1] = round;
    }

    char *n = (char *) calloc(b_len + a_len + 1, sizeof(char));
    round = 0;
    for (j = b_len + a_len - 1; j >= 0; j--) {
        int tmp = 0;
        for (i = b_len -1; i >= 0; i--) {
            tmp += m[i][j];
        }
        tmp += round;
        round = tmp / 10;
        n[j + 1] = tmp % 10 + '0';
    }
    n[0] = round + '0';
    //for (i = 0; i < b_len + a_len + 1; i++)
    //    printf("%c", n[i]);
    //printf("\n");

    char *result = calloc(b_len + a_len + 1 + 1 + 1, sizeof(char));
    for (j = 0, i = 0; j < b_len + a_len + 1; j++, i++) {
        if (dot_len && j + dot_len == b_len + a_len + 1) {
            result[j] = '.';
            i++;
        }
        result[i] = n[j];
    }
    result[i] = '\0';

    free(n);

    free(m[0]);
    free(m);

    free(a_int);
    free(b_int);
    return strstrip_zero(result);
}

char *strpow(char *a, int n)
{
    if (n == 0) return "1";
    if (strlen(a) == 0) return "0";
    char *tmp = a;
    while (n-- > 1) {
        tmp = multiply(a, tmp);
    }
    return tmp;
}

int main()
{
    char a[7];
    int b;

    while(scanf("%s%d", a, &b) != EOF) {
        printf("%s\n", strpow(strstrip_zero(a), b));
    }

    return 0;
}
