#include <stdio.h>
#include <stdlib.h>

int **h = NULL;
long **f = NULL;
struct sorth {
    long h;
    int r;
    int c;
};

struct sorth *sh = NULL;

int shcmp(const void *a, const void *b)
{
    return -((*(struct sorth *)a).h - (*(struct sorth *)b).h);
}

long max_height(i, j, m, n)
{
    if (f[i][j] > 0) {
        return f[i][j];
    }

    long fu, fd, fl, fr;
    fu = fd = fl = fr = 0;
    if (i - 1 >= 0 && h[i - 1][j] > h[i][j]) fu = max_height(i - 1, j, m, n);
    if (i + 1 < m && h[i + 1][j] > h[i][j]) fd = max_height(i + 1, j, m, n);
    if (j - 1 >= 0 && h[i][j - 1] > h[i][j]) fl = max_height(i, j - 1, m, n);
    if (j + 1 < n && h[i][j + 1] > h[i][j]) fr = max_height(i, j + 1, m, n);
    
    if (fd > fu) fu = fd;
    if (fl > fu) fu = fl;
    if (fr > fu) fu = fr;

    f[i][j] += fu + 1;
    
    return f[i][j];
}


int main()
{
    int m, n;
    int i, j;
    long mh;

    scanf("%d %d", &m, &n);

    h = (int **) malloc(m * sizeof(int *));
    f = (long **) malloc(m * sizeof(long *));
    h[0] = (int *) calloc(m * n, sizeof(int));
    f[0] = (long *) calloc(m * n, sizeof(long));
    sh = (struct sorth *) calloc(m * n, sizeof(struct sorth));

    for (i = 1; i < m; i++) {
        h[i] = h[i - 1] + n;
        f[i] = f[i - 1] + n;
    }


    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &h[i][j]);
            f[i][j] = 0;
            sh[i * n + j].r = i;
            sh[i * n + j].c = j;
            sh[i * n + j].h = h[i][j];
        }
    }
    qsort(&sh[0], (size_t) (m * n), sizeof(struct sorth), shcmp);

    for (i = 0; i < m * n; i++) {
        max_height(sh[i].r, sh[i].c, m, n);
    }

    mh = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (f[i][j] > mh) mh = f[i][j];
        }
    }
    printf("%ld\n", mh);

    return 0;
}
