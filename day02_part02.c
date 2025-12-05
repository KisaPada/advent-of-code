#include <stdio.h>
#include <string.h>

#define BUFSIZE 8192

int isDupeStr(char *s) {
    int slen = strlen(s);
    char subStr[32];
    int subStrCount;
    for (int subStrLen = 1; subStrLen <= slen / 2; subStrLen++) {
        if ((slen % subStrLen) != 0) continue;
        memset(subStr, 0, sizeof(subStr));
        memcpy(subStr, s, subStrLen);
        subStrCount = 0;
        char *ptr = s;
        while ((ptr = strstr(ptr, subStr))) {
            subStrCount++;
            ptr += subStrLen;
        }
        if ((subStrCount * subStrLen) == slen) return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    char s[BUFSIZE] = {0};

    FILE *f = fopen(argv[1], "r");
    if (!f) return perror("fopen"), -1;
    fgets(s, sizeof(s), f);
    fclose(f);

    unsigned long long lastSum = 0;
    unsigned long long sum = 0;

    unsigned long long leftLim = 0, rightLim = 0;
    char numStr[32] = {0};
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

    printf("Part 02: %llu\n", sum);

    return 0;
}
