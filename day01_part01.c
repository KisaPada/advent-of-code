#include <stdio.h>
#include <stdlib.h>

#define STARTNUM 50
#define MAXVAL 99
#define BUFSIZE 64

char strBuf[BUFSIZE] = {};

int turnRight(int currNum, int turnNum) {
    return (currNum + turnNum) % (MAXVAL + 1);
}

int turnLeft(int currNum, int turnNum) {
    currNum -= turnNum % 100;
    return (currNum >= 0) ? currNum : (MAXVAL + 1 + currNum);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: must provide path to input file as arg\n");
        return -1;
    }

    FILE *f = fopen(argv[1], "r");
    int currNum = STARTNUM;
    int turnNum, zeroCount = 0;
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
        if (currNum == 0) zeroCount++;
    }
    fclose(f);

    printf("Part 1 ans: %d\n", zeroCount);

    return 0;
}
