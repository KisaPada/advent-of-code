#include <stdio.h>
#include <stdlib.h>

#define STARTNUM    50
#define MAXVAL      99
#define MODULONUM   (MAXVAL + 1)
#define BUFSIZE     64

int zeroCount = 0;

int turnRight(int currNum, int turnNum) {
    int sum = currNum + turnNum;
    int rem = sum % MODULONUM;

    if (sum >= MODULONUM) {
        zeroCount += (sum - rem) / MODULONUM;
    }

    return rem;
}

int turnLeft(int currNum, int turnNum) {
    int mirrorNum = (MODULONUM - currNum) % 100;
    int newMirrorNum = turnRight(mirrorNum, turnNum);

    return (MODULONUM - newMirrorNum) % 100;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: must provide path to input file as arg\n");
        return -1;
    }

    char strBuf[BUFSIZE] = {};

    FILE *f = fopen(argv[1], "r");
    if (!f) return perror("Error opening file"), -1;
    int currNum = STARTNUM;
    int turnNum = 0;
    while (fgets(strBuf, BUFSIZE, f)) {
        turnNum = atoi(strBuf + 1);
        if (strBuf[0] == 'L') {
            currNum = turnLeft(currNum, turnNum);
        } else if (strBuf[0] == 'R') {
            currNum = turnRight(currNum, turnNum);
        } else {
            printf("Error: Leading char in line (%s) not recognized.\n", strBuf);
            fclose(f);
            return -1;
        }
    }
    fclose(f);

    printf("Part 2 ans: %d\n", zeroCount);

    return 0;
}
