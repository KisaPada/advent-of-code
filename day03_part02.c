#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMDIGITS 12

int main(int argc, char **argv) {
    if (argc != 2) return printf("Error: must provide path to input as argument."), -1;

    FILE *f = fopen(argv[1], "r");
    if (!f) return perror("fopen"), -1;

    unsigned long long sum = 0, lastSum = 0;
    int lidx = 0;
    char numStr[NUMDIGITS + 1] = {0};
    char s[1024] = {0};
    while (fgets(s, sizeof(s), f)) {
        int sLen = strlen(s);
        if (s[sLen - 1] == '\n') {
            s[--sLen] = '\0';
        }
        memset(numStr, 0, NUMDIGITS + 1);
        lidx = 0;
        for (int i = 0; i < NUMDIGITS; i++) {
            for (int j = lidx; j < sLen - (NUMDIGITS - 1 - i); j++) {
                if (s[j] > numStr[i]) {
                    numStr[i] = s[j];
                    lidx = j + 1;
                }
            }
        }
        lastSum = sum;
        sum += atoll(numStr);
        if (lastSum > sum) fprintf(stderr, "OVERFLOW!!\n");
    }

    printf("Part 02: %llu\n", sum);

    fclose(f);
    return 0;
}
