#include <stdio.h>
#include <stdlib.h>

typedef struct rangeNode {
    unsigned long long left, right;
    struct rangeNode *next;
} rangeNode;

int addRange(rangeNode *head, unsigned long long l, unsigned long long r) {
    rangeNode *newNode = (rangeNode *)malloc(sizeof(rangeNode));
    if (!newNode) {
        perror("addRangeNode->malloc");
        exit(-1);
    }
    newNode->left  = l;
    newNode->right = r;
    newNode->next  = NULL;

    if (head->next == NULL) {
        head->next = newNode;
        return 0;
    }

    rangeNode *ptr = head;
    while ((ptr->next != NULL) && () ptr = ptr->next; // TODO: Continue from here

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) return fprintf(stderr, "Error: must include path to input as arg\n"), -1;

    unsigned int count = 0;
    char s[256] = {0};

    FILE *f = fopen(argv[1], "r");
    rangeNode *rangeLL = (rangeNode *)calloc(1, sizeof(rangeNode));
    while ((fgets(s, sizeof(s), f)) && (s[0] != '\n')) {
        unsigned long long l, r;
        if (sscanf(s, "%llu-%llu", &l, &r) != 2) {
            fprintf(stderr, "(sscanf): bad read\n");
            return -1;
        }
        if (addRange(rangeLL, l, r) != 0) return fprintf(stderr, "(addrange): return != 0\n"), -1;
    }
    fclose(f);

    printf("Part 02: %d\n", count);

    return 0;
}
