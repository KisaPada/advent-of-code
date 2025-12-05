#include <stdio.h>
#include <string.h>

#define BUFSIZE 8192

int isDupeStr(char *s) {
    int isDupe = 0;

    return isDupe;
}

int main(int argc, char **argv) {
    char s[BUFSIZE] = {};

    FILE *f = fopen(argv[1], "r");
    if (!f) return perror("fopen"), -1;
    fgets(s, sizeof(s), f);
    fclose(f);

    unsigned long long lastSum = 0;
    unsigned long long sum = 0;

    unsigned long long leftLim = 0, rightLim = 0;
    char *lPtr = NULL, *mPtr = NULL, *rPtr = NULL;
    char numStr[32] = {};
    for (char *tok = strtok(s, ","); tok != NULL; tok = strtok(NULL, ",")) {
        if (sscanf(tok, "%llu-%llu", &leftLim, &rightLim) != 2) {
            fprintf(stderr, "bad range\n");
        }
        for (unsigned long long i = leftLim; i <= rightLim; i++) {
            if (!snprintf(numStr, sizeof(numStr), "%llu", i)) {
                fprintf(stderr, "bad snprintf\n");
            }
            if (isDupeStr(numStr)) {
                lastSum = sum;
                sum += i;
            }
            if (lastSum > sum) fprintf(stderr, "OVERFLOW!!\n");
        }
    }

    printf("Part 01: %llu\n", sum);

    return 0;
}
