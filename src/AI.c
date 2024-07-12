#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Disk {
    YELLOW = 1,
    RED = 0,
    EMPTY = -1,
};

struct minMaxNode{
    enum Disk state[42];
    int depth;
    int evaluation;
    int alpha;
    int beta;
    struct minMaxNode* parent;
    struct minMaxNode* ch0;
    struct minMaxNode* ch1;
    struct minMaxNode* ch2;
    struct minMaxNode* ch3;
    struct minMaxNode* ch4;
    struct minMaxNode* ch5;
    struct minMaxNode* ch6;
};

void getBoard (int* state) {
    int i = 0;
    int j = 0;
    printf("\n");
    for (i = 0; i<6; i++) {
        for (j = 0; j<7; j++) {
            printf("|");
            if (state[i*7 + j] == YELLOW) {
                printf("X");
            } else if (state[i*7 + j] == RED) {
                printf("O");
            } else {
                printf(" ");
            }
            printf("|");
        }
        printf("\n");
    }
    printf(" 1  2  3  4  5  6  7 \n\n");
}
