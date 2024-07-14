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

int* actions (int* state) {
    int actions[7] = {1, 1, 1, 1, 1, 1, 1};

    int i = 0;

    for (i = 0; i<7; i++) {
        if (state[i] != EMPTY) {
            actions[i] = 0;
        }
    }

    for (i = 0; i<7; i++) {
        printf("%d |", actions[i]);
    }
    printf("\n");

    int* p = actions;

    return p;
}

int* result (int* state, int col, int which) {
    int* pActions;
    pActions = actions(state);
    if (pActions[col] == 0) {
        return NULL;
    }

    int newState[42];
    int i = 0;
    for (i = 0; i<42; i++) {
        newState[i] = state[i];
    }
    i = 0;

    while (newState[i*7 + col] == EMPTY) {
        i++;
    }

    if (newState[i*7 + col] != EMPTY) {
        i--;
    }

    if (which == 0) {
        newState[i*7 + col] = RED;
    } else {
        newState[i*7 + col] = YELLOW;
    }

    int* p;

    p = newState;
    return p;
}

int evaluation (int* state) {
    enum Disk value = EMPTY;
    int i = 0;
    int j = 0;

    //checking if someone is winning
    //return -1 if the human wins, 1 if the AI wins, 0 if noone wins
    for (i = 0; i<6; i++) {
        //only check up, right, up.right, up-left
        for (j = 0; j<7; j++) {
            value = state[i*7 + j];
            if (value != EMPTY) {
                if (i>=3) {
                    //check up
                    if (state[(i-1)*7 + j] == value && state[(i-2)*7 + j] == value && state[(i-3)*7 + j] == value) {
                        if (value == RED) {
                            //human wins
                            return -1;
                        } else if (value == YELLOW) {
                            //AI wins
                            return 1;
                        }
                    }
                }
                

                if (j<=3) {
                    //check right
                    if (state[i*7 + j + 1] == value && state[i*7 + j + 2] == value && state[i*7 + j + 3] == value) {
                        if (value == RED) {
                            //human wins
                            return -1;
                        } else if (value == YELLOW) {
                            //AI wins
                            return 1;
                        }
                    }
                }


                if (i>=3 && j<=3) {
                    //check up-right
                    if (state[(i-1)*7 + j + 1] == value && state[(i-2)*7 + j + 2] == value && state[(i-3)*7 + j + 3] == value) {
                        if (value == RED) {
                            //human wins
                            return -1;
                        } else if (value == YELLOW) {
                            //AI wins
                            return 1;
                        }
                    }
                }


                if (i>=3 && j>=3) {
                    //check up-left
                    if (state[(i-1)*7 + j - 1] == value && state[(i-2)*7 + j - 2] == value && state[(i-3)*7 + j - 3] == value) {
                        if (value == RED) {
                            //human wins
                            return -1;
                        } else if (value == YELLOW) {
                            //AI wins
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
