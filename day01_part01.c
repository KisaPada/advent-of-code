#include <stdio.h>
#include <stdlib.h>

#define STARTNUM    50
#define MAXVAL      99
#define MODULONUM   (MAXVAL + 1)
#define BUFSIZE     64

int turnRight(int currNum, int turnNum) {
    return (currNum + turnNum) % MODULONUM;
}

int turnLeft(int currNum, int turnNum) {
    currNum -= turnNum % MODULONUM;
    return (currNum >= 0) ? currNum : (MODULONUM + currNum);
}

int main(int argc, char *argv[]) {
    if (argc != 2) return fprintf(stderr, "Error: must provide path to input file as arg\n"), -1;

    char strBuf[BUFSIZE] = {};

    FILE *f = fopen(argv[1], "r");
    if (!f) return perror("fopen"), -1;
    int currNum = STARTNUM;
    int turnNum, zeroCount = 0;
    while (fgets(strBuf, BUFSIZE, f)) {
        turnNum = atoi(strBuf + 1);
        if (strBuf[0] == 'L') currNum = turnLeft(currNum, turnNum);
        else if (strBuf[0] == 'R') currNum = turnRight(currNum, turnNum);
        else {
            fprintf(stderr, "Error: Leading char in line (%s) not recognized.", strBuf);
            fclose(f);
            return -1;
        }
        if (currNum == 0) zeroCount++;
    }
    fclose(f);

    printf("Part 1 ans: %d\n", zeroCount);

    return 0;
}
