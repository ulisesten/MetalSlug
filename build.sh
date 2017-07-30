#!/bin/bash

# -I/usr/include/SDL2 
# -L/usr/lib/x86_64-linux-gnu

#Compilando: 
gcc -o MetalSlug main.cpp floor.cpp -lSDL2_image `sdl2-config --cflags --libs`
#gcc -o pisos floor.cpp

if [ $? -ne 0 ]; then
    echo "[ERROR]Algo obviamente salió mal"
else
    echo "[MetalSlug]corriendo..."
    ./MetalSlug #ejecutando
    echo "[MetalSlug]bye"
fi
