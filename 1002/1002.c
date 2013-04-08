#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct BTNode {
    struct BTNode *p;
    struct BTNode *l;
    struct BTNode *r;
    char k[30 + 1];
    int v;
};

char charmap(char alph)
{
    switch (alph) {
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

void bt_insert(struct BTNode **root, struct BTNode *node)
{
    struct BTNode **p = root;
    struct BTNode **current = root;

    while (*p != NULL) {
        if (strcmp((*p)->k, node->k) == 0) {
            break;
        } else if (strcmp((*p)->k, node->k) < 0) {
            current = p;
            p = &((*p)->r);
        } else {
            current = p;
            p = &((*p)->l);
        }
    }

    if (p == root) {
        *root = node;
    } else {
        *p = node;
        (*p)->p = *current;
    }
}

struct BTNode *bt_search(struct BTNode *root, char *key)
{
    while (root != NULL) {
        if (strcmp(root->k, key) == 0) {
            break;
        } else if (strcmp(root->k, key) < 0) {
            root = root->r;
        } else {
            root = root->l;
        }
    }

    return root;
}

void bt_visit(struct BTNode *root)
{
    int i;
    if (root != NULL) {
        bt_visit(root->l);
        if (root->v > 1) {
            for (i=0; i<3; i++) printf("%c", root->k[i]);
            printf("-");
            for (i=3; i<7; i++) printf("%c", root->k[i]);
            printf(" %d\n", root->v);
        }
        bt_visit(root->r);
    }
}

int main()
{
    int n;
    char phone[20];
    struct BTNode *root = NULL;
    struct BTNode *node = NULL;

    scanf("%d", &n);
    while (n-- > 0) {
        scanf("%s", phone);
        char *new_phone = trans_phone(filter_phone(phone));
        node = bt_search(root, new_phone);
        if (node == NULL) {
            node = (struct BTNode *)(malloc(sizeof(struct BTNode)));
            node->p = node->l = node->r = NULL;
            strcpy(node->k, new_phone);
            node->v = 1;
            bt_insert(&root, node);
        } else {
            node->v++;
        }
    }

    bt_visit(root);

    return 0;
}
