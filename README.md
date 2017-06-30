
Ulises Martínez Elías

# MetalSlug
Replica de Metal Slug en C y SDL 2.0

## Instalando SDL2:

Abrir una terminal en este directorio e introducir el siguiente comando:

    sudo ./configure.sh

## Compilar y ejecutar:

    ./build.sh

## Ejecutar:

    ./MetalSlug

## Notas:

En caso de recibir el mensaje de error: Permiso denegado
Hay que dar permisos de ejecución a los archivos con extensión .sh

    sudo chmod a+x configure.sh
    sudo chmod a+x build.sh
    sudo chmod a+x MetalSlug

En caso de error a la hora de compilar revisar el archivo build.sh
y verificar que las rutas despues de -I y -L sean las correctas. En
las diferentes distribuciones de linux estas rutas pueden cambiar.

Para más información envíame un correo a ulises.mtz.el@gmail.com
