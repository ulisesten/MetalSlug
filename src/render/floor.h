#ifndef FLOOR_H
#define FLOOR_H

#include <stdio.h>
#include <stdlib.h>

short* readFloorCoords(const char* filename, int* count);

// Calcula la altura del piso en x
//void getAltura(int piso[]);

// Carga la trayectoria de salto
void clarkJump(int salto[]);

#endif
