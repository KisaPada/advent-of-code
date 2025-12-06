#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) return printf("Error: must provide path to input as argument."), -1;

    FILE *f = fopen(argv[1], "r");
    if (!f) return perror("fopen"), -1;

    unsigned long long sum = 0;
    char lchar = 0, rchar = 0;
    int lidx = 0;
    char s[256] = {0};
    while (fgets(s, sizeof(s), f)) {
        lchar = rchar = lidx = 0;
        for (int i = 0; i < strlen(s) - 2; i++) {
            if (s[i] > lchar) {
                lchar = s[i];
                lidx = i;
            }
        }
        for (int i = strlen(s) - 2; i > lidx; i--) {
            if (s[i] > rchar) {
                rchar = s[i];
            }
        }
        sum += ((lchar - '0') * 10) + (rchar - '0');
    }

    printf("Part 01: %llu\n", sum);

    fclose(f);
    return 0;
}
