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

float evaluation (int* state, int depth) {
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
                                } else if (state[(i-3)*7 + j]==YELLOW) {
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
                                } else if (state[i*7 + j + 3]==YELLOW) {
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
                            } else if (state[i*7 + j + 2]==YELLOW) {
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
                            } else if (state[i*7 + j + 1]==YELLOW) {
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
                                } else if (state[(i-3)*7 + j + 3]==YELLOW) {
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
                            } else if (state[(i-2)*7 + j + 2]==YELLOW) {
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
                            } else if (state[(i-1)*7 + j + 1]==YELLOW) {
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
                                } else if (state[(i-3)*7 + j - 3]==YELLOW) {
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
                            } else if (state[(i-2)*7 + j - 2]==YELLOW) {
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
                            } else if (state[(i-1)*7 + j - 1]==YELLOW) {
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
    float evaluation = wins*10 - losses*20 + AI_three_streaks*3 - human_three_streaks*3 - human_two_streaks*2 + AI_block_streak * 3;
    //printf("evaluation: %d*10 - %d*10 + %d*5 - %d*5 - %d*3 + %d*7 = %f\n", wins, losses, AI_three_streaks, human_three_streaks, human_two_streaks, AI_block_streak, evaluation);
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

struct minMaxNode* generateChild(struct minMaxNode** parent, int childNumber, int playing, struct minMaxNode** max, struct visitedState** closedList, int* total) {
    struct minMaxNode* child = malloc(sizeof(struct minMaxNode));
    int i = 0;
    int* a;
    int invertPlaying;
    struct visitedState* curr;
    struct minMaxNode* maxChildEv = NULL;
    struct minMaxNode* minChildEv = NULL;
    int is_equal = 0;

    child->state = result((*parent)->state, childNumber, playing);
    if (child->state == NULL) {
        free(child);
        return NULL;
    }
    curr = (*closedList);
    if ((*closedList)->next == NULL) {
        is_equal = 1;
    }
    while (curr->next!=NULL) {
        for (i = 0; i<42; i++) {
            if (child->state[i] != curr->state[i]) {
                is_equal = 1;
                break;
            }
        }
        curr = curr->next;
    }
    if (is_equal == 0) {
        //printf("FREEEING CHILD!!!!!!!!!!!!!!!!!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        free(child);
        return NULL;
    }

    struct visitedState* newNode = malloc(sizeof(struct visitedState*));
    newNode->state = child->state;
    newNode->next = NULL;
    curr->next = newNode;
    //printf("child number %d   ---   ", *total);
    a = actions(child->state);
    child->depth = (*parent)->depth + 1;
    if (child->depth>=5) {
        //printf("\n");
        free(child);
        return NULL;
    }
    child->parent = (*parent);
    child->evaluation = evaluation(child->state, child->depth);
    if (playing == 1) {
        invertPlaying = 0;
    } else {
        invertPlaying = 1;
    }
    child->MaxOrMin = invertPlaying;
    child->alpha = (*parent)->alpha;
    child->beta = (*parent)->beta;   

    if (is_win(child->state) != 0) {
        for (i = 0; i<7; i++) {
            child->children[i] = NULL;
        }

        return child;
    }

    int is_leaf = 0; //0 if leaf, 1 if not
    int is_child_leaf = 0; //0 if leaf, 1 if not
    int j = 0;
    for (i = 0; i<7; i++) {
        if (actions(child->state)[i]==1) {
            *total = *total + 1;
            child->children[i] = generateChild(&child, i, invertPlaying, max, closedList, total);
        } else {
            child->children[i] = NULL;
        }
    }
    return child;
}

void destroyTree(struct minMaxNode** root) {
    int i = 0;

    for (i = 0; i<7; i++) {
        if ((*root)->children[i]!=NULL) {
            destroyTree(&((*root)->children[i]));
        }
    }
    /*if ((*root)->state!=NULL) {
        free((*root)->state);
    }*/
    if ((*root)!=NULL) {
        free(*root);
    }
}

void destroyList (struct visitedState* head) {
    struct visitedState* curr = head->next;

    free(head);

    if (curr!=NULL) {
        destroyList(curr);
    }
}

int checkNode (struct minMaxNode* root) {
    int i = 0;
    struct minMaxNode* chosen = NULL;
    int is_leaf = 0; //0 if leaf, 1 if not
    for (i = 0; i<7; i++) {
        if (root->children[i]!=NULL) {
            is_leaf = 1;
            break;
        }
    }
    if (is_leaf == 0) {
        return root->evaluation;
    }

    if (root->MaxOrMin == 0) {
        //min node
        int minEv = INT_MAX;
        for (i = 0; i<7; i++) {
            if (root->children[i] != NULL) {
                if (root->children[i]->evaluation == minEv) {
                    if ((rand()%6) == 0) {
                        printf("changing curr -> %d ev: %f\n", i, root->children[i]->evaluation);
                        chosen = root->children[i];
                        minEv = root->children[i]->evaluation;
                    }
                }
                if (root->children[i]->evaluation < minEv) {
                    printf("changing curr -> %d ev: %f\n", i, root->children[i]->evaluation);
                    chosen = root->children[i];
                    minEv = root->children[i]->evaluation;
                }

                return checkNode(chosen);
            }
            return 0;
        }
        
    } else {
        //max node
        int maxEv = INT_MIN;
        int result;
        for (i = 0; i<7; i++) {
            if (root->children[i]!=NULL) {
                result = checkNode(root->children[i]);
                if (result > maxEv) {
                    maxEv = result;
                }
            }
        }
        return maxEv;
    }

}

/*int MinMax (int* state, int playing) {
    //playing is 1 if the AI is playing, 0 if the human is
    int check = 0;
    struct minMaxNode* root = malloc(sizeof(struct minMaxNode));
    struct minMaxNode* curr = NULL;
    int* a = actions(state);
    int i = 0;
    struct minMaxNode* max = root;
    struct visitedState* head = malloc(sizeof(struct visitedState));
    root->state = state;
    root->depth = 0;
    root->evaluation = evaluation(state, 0);
    root->parent = NULL;
    root->MaxOrMin = 1;
    root->alpha = INT_MIN;
    root->beta = INT_MAX;
    head->state = root->state;
    head->next = NULL;

    int total = 0;
    int* p = &total;

    for (i = 0; i<7; i++) {
        if (actions(root->state)[i]) {
            root->children[i] = generateChild(&root, i, playing, &max, &head, p);

            printf("generated child #%d of root\n", i);
            total++;
        } else {
            root->children[i] = NULL;
        }
    }

    //now go from max until root. When reached, get which move he made and return that move
    int is_leaf = 1; //0 if leaf, 1 if not
    int j = 0;
    struct minMaxNode* next = NULL;
    curr = root;
    srand(time(NULL));
    //for every max node I need to check all its children, then I choose the min node based on the minimum evaluation. When I reach a leaf, if it is a max node I need to pick the greatest, if it's a min I need to pick the smallest
    //root is always max node
    int result;
    int minEv = INT_MAX;
    int maxEv = INT_MIN;
    int move;
    for (i = 0; i<7; i++) {
        result = checkNode(curr->children[i]);
        if (result > maxEv) {
            maxEv = result;
            move = i;
        }
    }
    
    /*while (is_leaf!=0) {
        is_leaf = 0;
        for (i = 0; i<7; i++) {
            if (curr->children[i]!=NULL) {
                is_leaf = 1;
            }
        }
        if (is_leaf != 0) {
            if (curr->MaxOrMin == 1) {
                //max node
                printf("max node\n");
                int maxEv = INT_MIN;
                for (i = 0; i<7; i++) {
                    if (curr->children[i] != NULL) {
                        printf("i: %d -> %f\n", i, curr->children[i]->evaluation);
                        if (curr->children[i]->evaluation == maxEv) {
                            if ((rand()%6) == 0) {
                                printf("changing curr -> %d ev: %f\n", i, curr->children[i]->evaluation);
                                next = curr->children[i];
                                maxEv = curr->children[i]->evaluation;
                            }
                        }
                        if (curr->children[i]->evaluation > maxEv) {
                            printf("changing curr -> %d ev: %f\n", i, curr->children[i]->evaluation);
                            next = curr->children[i];
                            maxEv = curr->children[i]->evaluation;
                        }
                    }
                }
            } else {
                //min node
                printf("min node\n");
                int minEv = INT_MAX;
                for (i = 0; i<7; i++) {
                    if (curr->children[i] != NULL) {
                        if (curr->children[i]->evaluation == minEv) {
                            if ((rand()%6) == 0) {
                                printf("changing curr -> %d ev: %f\n", i, curr->children[i]->evaluation);
                                next = curr->children[i];
                                minEv = curr->children[i]->evaluation;
                            }
                        }
                        if (curr->children[i]->evaluation < minEv) {
                            printf("changing curr -> %d ev: %f\n", i, curr->children[i]->evaluation);
                            next = curr->children[i];
                            minEv = curr->children[i]->evaluation;
                        }
                    }
                }
            }

            curr = next;
            printf("curr->ev: %f\n\n", next->evaluation);
        }
    }*//*

    printf("final ev: %d\n", maxEv);

    return move;
    
    int count = 0;
    struct visitedState* list = head;
    while (curr->parent != root && curr->parent!=NULL) {
        curr = curr->parent;
    }
    for (i = 0; i<7; i++) {
        if (root->children[i] == curr) {
            while (list->next!=NULL) {
                count++;
                list = list->next;
            }
            printf("closed list size: %d\n", count);
            destroyList(head);
            //destroyTree(root);
            return i;
        }
    }
    
}*/

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
    int is_tie = 0; //0 if leaf, 1 if not
    int value;
    int i = 0;
    int j = 0;
    struct minMaxNode* child = NULL;

    if (depth == 0 || is_win((*node)->state) != 0) {
        (*node)->evaluation = evaluation((*node)->state, (*node)->depth);
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
    root->evaluation = evaluation(root->state, 0);
    
    for (i = 0; i<7; i++) {
        root->children[i] = NULL;
    }
    best_value = minmax(&root, 7, root->MaxOrMin, &total);

    
    for (i = 0; i<7; i++) {
        if (root->children!=NULL) {
            if (root->children[i]->evaluation == best_value) {
                destroyTree(&root);
                return i;
            }
        }
    }
}

