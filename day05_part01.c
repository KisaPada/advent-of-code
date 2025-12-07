#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) return fprintf(stderr, "Error: must include path to input as arg\n"), -1;

    unsigned int count = 0;
    char s[256] = {0};
    unsigned long long ranges[256][2] = {0};
    unsigned int rangeRows = 0;

    FILE *f = fopen(argv[1], "r");
    while ((fgets(s, sizeof(s), f)) && (s[0] != '\n')) {
        if (sscanf(s, "%llu-%llu", &ranges[rangeRows][0], &ranges[rangeRows][1]) != 2) {
            fprintf(stderr, "(sscanf): bad read\n");
            return -1;
        }
        rangeRows++;
    }
    while (fgets(s, sizeof(s), f)) {
        unsigned long long num;
        if (!sscanf(s, "%llu", &num)) return perror("sscanf"), -1;
        int inRange = 0;
        for (int i = 0; i < rangeRows; i++) {
            if ((ranges[i][0] < num) && (num < ranges[i][1])) {
                inRange = 1;
                break;
            }
            if (inRange) break;
        }
        if (inRange) count++;
    }
    fclose(f);

    printf("Part 01: %d\n", count);

    return 0;
}
