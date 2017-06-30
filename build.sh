#!/bin/bash

#Compilando: 
gcc -o MetalSlug main.cpp -I/usr/include/SDL2 -L/usr/lib/x86_64-linux-gnu -lSDL2_image `sdl2-config --cflags --libs`
if [ $? -ne 0 ]; then
echo "[ERROR]Algo obviamente salió mal"
else
./MetalSlug #ejecutando
echo "Corriendo..."
fi
