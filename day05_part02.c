#include <stdio.h>
#include <stdlib.h>

typedef struct rangeNode {
    unsigned long long left, right;
    struct rangeNode *next;
} rangeNode;

void freeLL(rangeNode *headPtr) {
    rangeNode *currNode = headPtr;
    rangeNode *nextNode;
    while ((nextNode = currNode->next) != NULL) {
        free(currNode);
        currNode = nextNode;
    }
    free(currNode);
    return;
}

void addRange(rangeNode *headPtr, unsigned long long l, unsigned long long r) {
    rangeNode *newNode = (rangeNode *)malloc(sizeof(rangeNode));
    if (!newNode) {
        perror("addRangeNode->malloc");
        exit(-1);
    }
    newNode->left  = l;
    newNode->right = r;
    newNode->next  = NULL;

    if (headPtr->next == NULL) {
        headPtr->next = newNode;
        return;
    }

    rangeNode *lptr = headPtr; // lptr points to rangeNode whose left bound is <= l
    while ((lptr->next != NULL) && (lptr->next->left > l)) lptr = lptr->next;
    if (lptr->next == NULL) {
        lptr->next = newNode;
        return;
    } else lptr = lptr->next;

    rangeNode *rptr = lptr; // rptr points to rangeNode before rangeNode whose right bound >= r
    while (rptr->next->left <= r) rptr = rptr->next;

    if () {} // TODO: continue here -- simply insert if can
    if (l < lptr->right) { // TODO: make left grow to match, remove others if needed
        if (r > lptr->right) lptr->right = r;
    }

    // if (lptr == rptr) {
    //     if (l < lptr->left) lptr->left = l;
    //     if (r > lptr->right) lptr->right = r;
    //     free(newNode);
    // }

    return;
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
