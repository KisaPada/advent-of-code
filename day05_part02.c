#include <stdio.h>
#include <stdlib.h>

typedef struct rangeNode {
    unsigned long long left, right;
    struct rangeNode *next;
} rangeNode;

unsigned long long countRange(rangeNode *headPtr) {
    unsigned long long count = 0;
    rangeNode *ptr = headPtr;

    while ((ptr = ptr->next) != NULL)
        count += ptr->right - ptr->left + 1;

    return count;
}

void printLL(rangeNode *headPtr) {
    rangeNode *ptr = headPtr;
    while ((ptr = ptr->next) != NULL)
        printf("%15llu - %15llu --> \n", ptr->left, ptr->right);
    printf("NULL\n");
    return;
}

void freeLL(rangeNode *headPtr) {
    if (headPtr == NULL) return;
    rangeNode *currNode = headPtr;
    rangeNode *nextNode;
    while ((nextNode = currNode->next) != NULL) {
        free(currNode);
        currNode = nextNode;
    }
    free(currNode);
    return;
}

int addRange(rangeNode *headPtr, unsigned long long l, unsigned long long r) {
    rangeNode *newNode = (rangeNode *)malloc(sizeof(rangeNode));
    if (!newNode) return perror("addRangeNode->malloc"), -1;

    newNode->left  = l;
    newNode->right = r;
    newNode->next  = NULL;

    if (headPtr->next == NULL) {
        headPtr->next = newNode;
        return 0;
    }

    rangeNode *lptr = headPtr;
    while ((lptr->next != NULL) && (lptr->next->left <= l)) lptr = lptr->next;
    if (l <= lptr->right) {
        free(newNode);
        if (r <= lptr->right) return 0;
        lptr->right = r;
        if (lptr->next == NULL) return 0;
    } else {
        if (lptr->next == NULL) {
            lptr->next = newNode;
            return 0;
        }
        newNode->next = lptr->next;
        lptr->next = newNode;
        lptr = newNode;
    }

    rangeNode *rptr = lptr;
    while ((rptr->next != NULL) && (rptr->next->left <= r)) rptr = rptr->next;
    if (r <= rptr->right) {
        lptr->right = rptr->right;
    }

    if (lptr == rptr) return 0;
    rangeNode *tptr = lptr->next;
    lptr->next = rptr->next;
    rptr->next = NULL;
    freeLL(tptr);

    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) return fprintf(stderr, "Error: must include path to input as arg\n"), -1;

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


    printf("Part 02: %llu\n", countRange(rangeLL));

    return 0;
}
