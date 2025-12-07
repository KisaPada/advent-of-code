#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) return fprintf(stderr, "Error: must provide path to input as argument\n"), -1;

    FILE *f = fopen(argv[1], "r");
    if (!f) return perror("fopen"), -1;


    char m[256][256] = {0};
    char s[256] = {0};
    int rows = 0;
    while (fgets(s, sizeof(s), f)) {
        int slen = strlen(s);
        if ((s[slen - 1]) == '\n') {
            s[--slen] = '\0';
        }
        memcpy(m[rows++], s, slen);
    }
    fclose(f);

    int sum = 0, lastSum = -1;
    while (sum != lastSum) {
        lastSum = sum;
        for (int i = 0; i < rows; i++) {
            int slen = strlen(m[i]);
            for (int j = 0; j < slen; j++) {
                if (m[i][j] != '@') continue;
                int adjRolls = 0;
                for (int k = i - 1; k <= i + 1; k++) {
                    if ((k < 0) || (k == rows)) continue;
                    for (int l = j - 1; l <= j + 1; l++) {
                        if (((k == i) && (l == j)) || (l < 0) || (l == slen)) continue;
                        if (m[k][l] == '@') adjRolls++;
                    }
                }
                if (adjRolls < 4) {
                    m[i][j] = '.';
                    sum++;
                }
            }
        }
    }

    printf("Part 02: %d\n", sum);

    return 0;
}
