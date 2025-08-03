#ifndef __UTILS_LISTS__
#define __UTILS_LISTS__

#include <stdio.h>
#include <stdlib.h>
#include "../animation/animation.h"

typedef struct node {
    BulletState bull_state;
    struct node *next;
}*BulletList;

//typedef list_node* List;

int createNode(BulletList* list_node, BulletState bull_state);
int add(BulletList* list_index, BulletState bull_state);


#endif