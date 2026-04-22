#include "utils.h"
#include "../animation/animation_enemies.h"
#include <stdio.h>
#include <stdlib.h>

EnemyMatrixData* readEnemyMatrix(const char* filename, short* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open %s\n", filename);
        *count = 0;
        return NULL;
    }

    short tempType, tempMode;
    int tempX, tempY;
    int items = 0;

    while (fscanf(file, "%hd %hd %d %d", &tempType, &tempMode, &tempX, &tempY) == 4) {
        items++;
    }

    *count = items;
    EnemyMatrixData* data = (EnemyMatrixData*)malloc(sizeof(EnemyMatrixData) * items);

    rewind(file);
    items = 0;
    while (fscanf(file, "%hd %hd %d %d", &data[items].type, &data[items].mode, &data[items].x, &data[items].y) == 4) {
        items++;
    }

    fclose(file);
    return data;
}
