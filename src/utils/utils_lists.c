#include "utils_lists.h"

int createNode(BulletList* ist_node, BulletState bull_state) {
    *ist_node= (BulletList)malloc(sizeof(struct node));
    if(*ist_node) {
        (*ist_node)->bull_state = bull_state;
        (*ist_node)->next = NULL;
        return 1;
    }

    return 0;
}

int add(BulletList* list_index, BulletState bull_state) {
    if(!*list_index) {
        return createNode(list_index, bull_state);
    }

    return 0;
}