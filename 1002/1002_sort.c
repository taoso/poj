#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char charmap(char alph)
{
    switch (toupper(alph)) {
        case 'A': case 'B': case 'C':
            return '2';
        case 'D': case 'E': case 'F':
            return '3';
        case 'G': case 'H': case 'I':
            return '4';
        case 'J': case 'K': case 'L':
            return '5';
        case 'M': case 'N': case 'O':
            return '6';
        case 'P': case 'R': case 'S':
            return '7';
        case 'T': case 'U': case 'V':
            return '8';
        case 'W': case 'X': case 'Y':
            return '9';
    }
    return alph;
}

char *trans_phone(char *phone)
{
    char *p = phone;
    while (*p) {
        *p = charmap(*p);
        p++;
    }

    return phone;
}

char *filter_phone(char *phone)
{
    int len = strlen(phone);
    char *new_phone = (char *) calloc(len + 1, sizeof(char));
    char *p, *q;
    p = phone;
    q = new_phone;
    while (*p) {
        if (isalnum(*p)) {
            *q = *p;
            q++;
        }
        p++;
    }
    *q = '\0';
    return new_phone;
}

uint32_t phone2int(char *phone)
{
    uint32_t base[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    uint32_t key = 0;
    int i = strlen(phone) - 1;
    while (*phone) {
        key += (uint32_t)(*phone - '0') * base[i--];
        phone++;
    }

    return key;
}

char *int2phone(uint32_t key, char *phone)
{
    int i;
    phone[8] = '\0';
    for (i = 7; i >= 0; i--) {
        if (i == 3) {
            phone[i] = '-';
        } else {
            phone[i] = (char)((key % 10) + '0');
            key /= 10;
        }
    }
}

int intcmp (const void *a, const void *b)
{
    return (*(int *)a - *(int*)b);
}

int main()
{
    long n, i;
    // TODO a little range cause 11565
    char phone[81];
    uint32_t key;
    uint32_t phones[100010];
    struct {
        uint32_t v;
        uint32_t c;
    } counter;
    int dupflag = 0;

    scanf("%ld", &n);
    i = 0;
    while (i < n) {
        scanf("%s\n", phone);
        phones[i++] = phone2int(trans_phone(filter_phone(phone)));
    }
    qsort(&phones[0], (size_t)n, sizeof(uint32_t), intcmp);
    counter.v = -1;
    counter.c = 1;
    for (i = 0; i < n; i++) {
        if (phones[i] == counter.v) {
            counter.c++;
        } else {
            if (counter.c > 1) {
                int2phone(counter.v, phone);
                printf("%s %d\n", phone, counter.c);
                dupflag = 1;
            }
            counter.v = phones[i];
            counter.c = 1;
        }
    }
    if (counter.c > 1) {
        int2phone(counter.v, phone);
        printf("%s %d\n", phone, counter.c);
        dupflag = 1;
    }

    if (dupflag == 0) {
        printf("No duplicates.\n");
    }

    return 0;
}
