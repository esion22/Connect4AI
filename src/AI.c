#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INT_MIN -2147483647
#define INT_MAX 2147483647

enum Disk {
    YELLOW = 1,
    RED = 0,
    EMPTY = -1,
};

struct minMaxNode{
    int* state;
    int depth;
    float evaluation;
    int alpha;
    int beta;
    int MaxOrMin; //1 for max, 0 for min
    struct minMaxNode* parent;
    struct minMaxNode* children[7];
};

struct visitedState {
    int* state;
    struct visitedState* next;
    struct visitedState* prev;
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

    int* p = actions;

    return p;
}

int* result (int* state, int col, int which) {
    int* pActions;
    pActions = actions(state);
    if (pActions[col] == 0) {
        return NULL;
    }

    int* newState = malloc(sizeof(int)*42);
    int i = 0;
    for (i = 0; i<42; i++) {
        newState[i] = state[i];
    }
    i = 0;

    while (newState[i*7 + col] == EMPTY && i!=5) {
        i++;
    }

    if (newState[i*7 + col] != EMPTY) {
        if (i<0) {
            printf("i minore di 0\n");
        }
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

float evaluation (int* state, int* prev_state, int depth) {
    enum Disk value = EMPTY;
    int i = 0;
    int j = 0;
    int wins = 0;
    int losses = 0;
    int AI_three_streaks = 0;
    int human_three_streaks = 0;
    int AI_block_streak = 0;
    int human_two_streaks = 0;

    //checking if someone is winning
    //return -1 if the human wins, 1 if the AI wins, 0 if noone wins
    for (i = 0; i<6; i++) {
        //only check up, right, up.right, up-left
        for (j = 0; j<7; j++) {
            value = state[i*7 + j];
            if (value != EMPTY) {
                if (i>=3) {
                    //check up
                    if (state[(i-1)*7 + j] == value) {
                        if (state[(i-2)*7 + j] == EMPTY && state[(i-3)*7 + j] == EMPTY) {
                            if (value == RED) {
                                human_two_streaks++;
                            }
                        } else if (state[(i-2)*7 + j] == value) {
                            //checking for 3 disk streaks
                            if (value == RED) {
                                if (state[(i-3)*7 + j] == EMPTY) {
                                    human_three_streaks++;
                                } else if (state[(i-3)*7 + j]==YELLOW/* && prev_state[(i-3)*7 + j]==EMPTY*/) {
                                    //AI blocks human streak
                                    AI_block_streak++;
                                }
                            } else if (state[(i-3)*7 + j] == EMPTY && value == YELLOW) {
                                AI_three_streaks++;
                            }
                            if (state[(i-3)*7 + j] == value) {
                                if (value == RED) {
                                    //human wins
                                    losses++;
                                } else if (value == YELLOW) {
                                    //AI wins
                                    wins++;
                                }
                            }
                        }
                        
                    } 
                }
                

                if (j<=3) {
                    //check right
                    if (state[i*7 + j + 1] == value) {
                        if (state[i*7 + j + 2] == EMPTY && state[i*7 + j + 3] == EMPTY) {
                            human_two_streaks++;
                        } else if (state[i*7 + j + 2] == value) {
                            //checking for 3 disk streaks
                            if (value == RED) {
                                if (state[i*7 + j + 3] == EMPTY) {
                                    human_three_streaks++;
                                } else if (state[i*7 + j + 3]==YELLOW/* && prev_state[i*7 + j + 3] == EMPTY*/) {
                                    //AI blocks human streak
                                    AI_block_streak++;
                                }
                            } else if (state[i*7 + j + 3] == EMPTY && value == YELLOW) {
                                AI_three_streaks++;
                            }
                        
                            if (state[i*7 + j + 3] == value) {
                                if (value == RED) {
                                    //human wins
                                    losses++;
                                } else if (value == YELLOW) {
                                    //AI wins
                                    wins++;
                                }
                            }
                        }
                    } else if (state[i*7 + j + 1] == value && state[i*7 + j + 3] == value) {
                        //checking for 3 disk streaks
                        if (value == RED) {
                            if (state[i*7 + j + 2] == EMPTY) {
                                human_three_streaks++;
                            } else if (state[i*7 + j + 2]==YELLOW/* && prev_state[i*7 + j + 2]==EMPTY*/) {
                                //AI blocks human streak
                                AI_block_streak++;
                            }
                        } else {
                            AI_three_streaks++;
                        }
                    } else if (state[i*7 + j + 2] == value && state[i*7 + j + 3] == value) {
                        //checking for 3 disk streaks
                        if (value == RED) {
                            if (state[i*7 + j + 1] == EMPTY) {
                                human_three_streaks++;
                            } else if (state[i*7 + j + 1]==YELLOW/* && prev_state[i*7 + j + 1]==EMPTY*/) {
                                //AI blocks human streak
                                AI_block_streak++;
                            }
                        } else {
                            AI_three_streaks++;
                        }
                    }
                }


                if (i>=3 && j<=3) {
                    //check up-right
                    if (state[(i-1)*7 + j + 1] == value) {
                        if (state[(i-2)*7 + j + 2] == EMPTY && state[(i-3)*7 + j + 3] == EMPTY) {
                            human_two_streaks++;
                        } else if (state[(i-2)*7 + j + 2] == value) {
                            //checking for 3 disk streaks
                            if (value == RED) {
                                if (state[(i-3)*7 + j + 3] == EMPTY) {
                                    human_three_streaks++;
                                } else if (state[(i-3)*7 + j + 3]==YELLOW/* && prev_state[(i-3)*7 + j + 3]==EMPTY*/) {
                                    //AI blocks human streak
                                    AI_block_streak++;
                                }
                            } else if (state[(i-3)*7 + j + 3] == EMPTY && value == YELLOW) {
                                AI_three_streaks++;
                            }
                            if (state[(i-3)*7 + j + 3] == value) {
                                if (value == RED) {
                                    //human wins
                                    losses++;
                                } else if (value == YELLOW) {
                                    //AI wins
                                    wins++;
                                }
                            }
                        }
                    } else if (state[(i-1)*7 + j + 1] == value && state[(i-3)*7 + j + 3] == value) {
                        //checking for 3 disk streaks
                        if (value == RED) {
                            if (state[(i-2)*7 + j + 2] == EMPTY) {
                                human_three_streaks++;
                            } else if (state[(i-2)*7 + j + 2]==YELLOW/* && prev_state[(i-2)*7 + j + 2]==EMPTY*/) {
                                //AI blocks human streak
                                AI_block_streak++;
                            }
                        } else {
                            AI_three_streaks++;
                        }
                    } else if (state[(i-2)*7 + j + 2] == value && state[(i-3)*7 + j + 3] == value) {
                        //checking for 3 disk streaks
                        if (value == RED) {
                            if (state[(i-1)*7 + j + 1] == EMPTY) {
                                human_three_streaks++;
                            } else if (state[(i-1)*7 + j + 1]==YELLOW/* && prev_state[(i-1)*7 + j + 1]==EMPTY*/) {
                                //AI blocks human streak
                                AI_block_streak++;
                            }
                        } else {
                            AI_three_streaks++;
                        }
                    }
                }


                if (i>=3 && j>=3) {
                    //check up-left
                    if (state[(i-1)*7 + j - 1] == value && state[(i-2)*7 + j - 2] == value) {
                        if (state[(i-2)*7 + j - 2] == EMPTY && state[(i-3)*7 + j - 3] == EMPTY) {
                            human_two_streaks++;
                        } else if (state[(i-2)*7 + j - 2] == value) {
                            //checking for 3 disk streaks
                            if (value == RED) {
                                if (state[(i-3)*7 + j - 3] == EMPTY) {
                                    human_three_streaks++;
                                } else if (state[(i-3)*7 + j - 3]==YELLOW/* && prev_state[(i-3)*7 + j - 3]==EMPTY*/) {
                                    //AI blocks human streak
                                    AI_block_streak++;
                                }
                            } else if (state[(i-3)*7 + j - 3] == EMPTY && value == YELLOW) {
                                AI_three_streaks++;
                            }
                            if (state[(i-3)*7 + j - 3] == value) {
                                if (value == RED) {
                                    //human wins
                                    losses++;
                                } else if (value == YELLOW) {
                                    //AI wins
                                    wins++;
                                }
                            }
                        }
                    } else if (state[(i-1)*7 + j - 1] == value && state[(i-3)*7 + j - 3] == value) {
                        //checking for 3 disk streaks
                        if (value == RED) {
                            if (state[(i-2)*7 + j - 2] == EMPTY) {
                                human_three_streaks++;
                            } else if (state[(i-2)*7 + j - 2]==YELLOW/* && prev_state[(i-2)*7 + j -2]==EMPTY*/) {
                                //AI blocks human streak
                                AI_block_streak++;
                            }
                        } else {
                            AI_three_streaks++;
                        }
                    }  else if (state[(i-2)*7 + j - 2] == value && state[(i-3)*7 + j - 3] == value) {
                        //checking for 3 disk streaks
                        if (value == RED) {
                            if (state[(i-1)*7 + j - 1] == EMPTY) {
                                human_three_streaks++;
                            } else if (state[(i-1)*7 + j - 1]==YELLOW/* && prev_state[(i-1) + j - 1]==EMPTY*/) {
                                //AI blocks human streak
                                AI_block_streak++;
                            }
                        } else {
                            AI_three_streaks++;
                        }
                    }
                }
            }
        }
    }
    float evaluation;

    evaluation = wins*10 - losses*20 + AI_three_streaks*3 - human_three_streaks*3 - human_two_streaks*2 + AI_block_streak*3;
    return evaluation;
}


int is_win (int* state) {
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
                    if (state[(i-1)*7 + j] == value && state[(i-2)*7 + j] == value) {
                        //checking for 3 disk streaks
                        if (state[(i-3)*7 + j] == value) {
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
                

                if (j<=3) {
                    //check right
                    if (state[i*7 + j + 1] == value && state[i*7 + j + 2] == value) {
                        if (state[i*7 + j + 3] == value) {
                            if (value == RED) {
                                //human wins
                                return 1;
                            } else if (value == YELLOW) {
                                //AI wins
                                return -1;
                            }
                        }
                    }
                }


                if (i>=3 && j<=3) {
                    //check up-right
                    if (state[(i-1)*7 + j + 1] == value && state[(i-2)*7 + j + 2] == value) {
                        if (state[(i-3)*7 + j + 3] == value) {
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


                if (i>=3 && j>=3) {
                    //check up-left
                    if (state[(i-1)*7 + j - 1] == value && state[(i-2)*7 + j - 2] == value) {
                        if (state[(i-3)*7 + j - 3] == value) {
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
    }

    return 0;
}

void destroyTree(struct minMaxNode** root) {
    int i = 0;

    for (i = 0; i<7; i++) {
        if ((*root)->children[i]!=NULL) {
            destroyTree(&((*root)->children[i]));
        }
    }
    if ((*root)!=NULL) {
        free(*root);
    }
}

void destroyList (struct visitedState** head) {
    struct visitedState* curr = (*head)->next;

    free(*head);

    if (curr!=NULL) {
        destroyList(&curr);
    }
}

float max (float num1, float num2) {
    if (num1>=num2) {
        return num1;
    } else {
        return num2;
    }
}

float min (float num1, float num2) {
    if (num1<=num2) {
        return num1;
    } else {
        return num2;
    }
}

float minmax (struct minMaxNode** node, int depth, int maximizing_player, int* total) {
    int value;
    int i = 0;
    int j = 0;
    struct minMaxNode* child = NULL;
    int isTie = 1; //0 if not Tie, 1 if Tie

    for (i = 0; i<7; i++) {
        if (actions((*node)->state)[i] == 1) {
            isTie = 0;
            break;
        }
    }

    if (depth == 0 || is_win((*node)->state) != 0 || isTie == 1) {
        (*node)->evaluation = evaluation((*node)->state, (*node)->parent->state, (*node)->depth);
        return (*node)->evaluation;
    }

    //now I have to create the node's children and analyze them
    if ((*node)!=NULL) {
        if (maximizing_player == 1) {
            //max node
            value = INT_MIN;
            for (i = 0; i<7; i++) {
                if (actions((*node)->state)[i] == 1) {
                    child = malloc(sizeof(struct minMaxNode));
                    child->depth = (*node)->depth + 1;
                    child->MaxOrMin = 0;
                    child->parent = (*node);
                    child->state = result((*node)->state, i, maximizing_player);
                    if (child->state != NULL) {
                        for (j = 0; j<7; j++) {
                            child->children[j] = NULL;
                        }
                        (*total)++;
                        //printf("child #%d\n", (*total));
                        (*node)->children[i] = child;

                        value = max(value, minmax(&child, depth - 1,  child->MaxOrMin, total));
                        }
                } else {
                    value = 0;
                }
            }
            (*node)->evaluation = value;
            return value;
        } else {
            //min node
            value = INT_MAX;
            for (i = 0; i<7; i++) {
                if (actions((*node)->state)[i] == 1) {
                    child = malloc(sizeof(struct minMaxNode));
                    child->depth = (*node)->depth + 1;
                    child->MaxOrMin = 1;
                    child->parent = (*node);
                    child->state = result((*node)->state, i, maximizing_player);

                    if (child->state != NULL) {
                        for (j = 0; j<7; j++) {
                            child->children[j] = NULL;
                        }

                        (*node)->children[i] = child;
                        (*total)++;
                        //printf("child #%d\n", (*total));
                        value = min(value, minmax(&child, depth - 1,  child->MaxOrMin, total));
                    }
                } else {
                    value = 0;
                }
            }
            (*node)->evaluation = value;
            return value;
        }
    } else {
        return 0;
    }
}

float alpha_beta_pruning (struct minMaxNode** node, int depth, int alpha, int beta, int maximizing_player, int* total) {
    int value;
    int i = 0;
    int j = 0;
    struct minMaxNode* child = NULL;
    int isTie = 1; //0 if not Tie, 1 if Tie

    for (i = 0; i<7; i++) {
        if (actions((*node)->state)[i] == 1) {
            isTie = 0;
            break;
        }
    }

    if (depth == 0 || is_win((*node)->state) != 0 || isTie == 1) {
        (*node)->evaluation = evaluation((*node)->state, (*node)->parent->state, (*node)->depth);
        return (*node)->evaluation;
    }

    if ((*node)!=NULL) {
        if (maximizing_player == 1) {
            //max node
            value = INT_MIN;
            for (i = 0; i<7; i++) {
                if (actions((*node)->state)[i] == 1) {
                    child = malloc(sizeof(struct minMaxNode));
                    child->depth = (*node)->depth + 1;
                    child->MaxOrMin = 0;
                    child->parent = (*node);
                    child->state = result((*node)->state, i, maximizing_player);
                    if (child->state != NULL) {
                        for (j = 0; j<7; j++) {
                            child->children[j] = NULL;
                        }
                        (*total)++;
                        //printf("child #%d\n", (*total));
                        (*node)->children[i] = child;

                        value = max(value, alpha_beta_pruning(&child, depth - 1, alpha, beta, child->MaxOrMin, total));
                        
                        alpha = max(alpha, value);

                        if (value >= beta) {
                            free(child);
                            (*node)->children[i] = NULL;
                            break; //beta cutoff
                        }
                    }
                }
            }
            (*node)->evaluation = value;
            return value;
        } else {
            //min node
            value = INT_MAX;
            for (i = 0; i<7; i++) {
                if (actions((*node)->state)[i] == 1) {
                    child = malloc(sizeof(struct minMaxNode));
                    child->depth = (*node)->depth + 1;
                    child->MaxOrMin = 0;
                    child->parent = (*node);
                    child->state = result((*node)->state, i, maximizing_player);
                    if (child->state != NULL) {
                        for (j = 0; j<7; j++) {
                            child->children[j] = NULL;
                        }
                        (*total)++;
                        //printf("child #%d\n", (*total));
                        (*node)->children[i] = child;

                        value = min(value, alpha_beta_pruning(&child, depth - 1, alpha, beta, child->MaxOrMin, total));
                        
                        beta = min(beta, value);

                        if (value <= alpha) {
                            free(child);
                            (*node)->children[i] = NULL;
                            break; //alpha cutoff
                        }
                    }
                }
            }
            (*node)->evaluation = value;
            return value;
        }
    } else {
        return 0;
    }
}

int getPlay (int* state) {
    int i = 0;
    int move = 0;
    int total = 0;
    float best_value = INT_MIN;
    struct minMaxNode* root = malloc(sizeof(struct minMaxNode));
    root->depth = 0;
    root->MaxOrMin = 1; //max
    root->parent = NULL;
    root->state = state;
    root->evaluation = evaluation(root->state, root->state, 0);
    
    for (i = 0; i<7; i++) {
        root->children[i] = NULL;
    }
    //best_value = minmax(&root, 7, root->MaxOrMin, &total);
    best_value = alpha_beta_pruning(&root, 7, INT_MIN, INT_MAX, root->MaxOrMin, &total);

    
    for (i = 0; i<7; i++) {
        if (root->children[i]!=NULL) {
            if (root->children[i]->evaluation == best_value) {
                printf("delivering %d\n", i);
                printf("explored %d nodes\n", total);
                destroyTree(&root);
                return i;
            }
        }
    }
}

