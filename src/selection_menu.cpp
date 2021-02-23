#include "selection_menu.h"


void menuPersonaje(SDL_Surface* screen,SDL_Window* window){//Funcion para elegir personaje

    SDL_Surface* image=NULL;//Puntero a imagen
    SDL_Event tecla;
    int arr[4],copia[4],i=0;

    int flag=IMG_INIT_PNG;//Iniciando soporte PNG
    IMG_Init(flag);//Iniciando soporte IMG

    if((IMG_Init(flag)&flag)){//Manejo de error
        image=IMG_Load("assets/select.png");//Cargando imagen
        if(image) {//Manejo de error
            copia[0]  =  309;  copia[1]  =  374;//Coordenadas de sector copiado
            copia[2]  =  441;  copia[3]  =  508;

            arr  [0]  =  18 ;  arr  [1]  =  83;//Coordenadas de inserciÃ³n de copia
            arr  [2]  =  150;  arr  [3]  =  217;

            while(true){
                if(SDL_PollEvent(&tecla)){//Capturando teclas
                    if(tecla.type==SDL_QUIT)
                        exit(0);
                    if(tecla.type==SDL_KEYDOWN){
                        if(tecla.key.keysym.sym==SDLK_ESCAPE)//Salir
                            exit(0);
                        if(tecla.key.keysym.sym==SDLK_RIGHT && i<3){//Derecha
                            i++;
                        }
                        if(tecla.key.keysym.sym==SDLK_LEFT && i>0){//Izquierda
                            i--;
                        }
                        if(tecla.key.keysym.sym==SDLK_f){//Pantalla completa
                            //ToggleFullscreen(window);//Necesita trabajo
                        }
                    }
                }

                animEscotilla( screen,image);
                elementosMenu( screen,image);
                select(        screen,image,copia[i],arr[i]);
                SDL_UpdateWindowSurface(window);//Refrescando pantalla
                
            }
        } else {
            
            printf("IMG_Load: %s\n", IMG_GetError());

        }

    } else {

        printf("Error IMG_Init %s",IMG_GetError());

    }

}

void elementosMenu(SDL_Surface* screen, SDL_Surface* image){
    SDL_Rect frame;//Marco de seleccion
        frame.x  =    4;
        frame.y  =  107;
        frame.w  =  305;
        frame.h  =  223;
    SDL_Rect marF;//Mostrando rostros inactivos
        marF.x   =  309; marF.y  =    3;
        marF.w   =  364; marF.h  =  121;
    SDL_Rect marC;
        marC.x   =  18;
        marC.y   =  73;

    SDL_BlitSurface(image,&frame,screen,NULL);//Marco
    SDL_BlitSurface(image,&marF, screen,&marC);//Rostros inactivos
}

void animEscotilla(SDL_Surface* screen,SDL_Surface* image){
    SDL_Rect door;//Escotilla
        door.x   =  0;  door.y  =  335;
        door.w   = 68;  door.h  =  134;
    SDL_Rect coorDoor;
        coorDoor.x  =  12;
        coorDoor.y  =  63;

    SDL_BlitSurface(image,&door,screen,&coorDoor);//Escotilla
}

void select(SDL_Surface* screen,SDL_Surface* image,int copia,int coor){
    SDL_Rect perFrame;//Seleccion
        perFrame.x   =   copia;  perFrame.y  =  125;
        perFrame.w   =   68   ;  perFrame.h  =  122;

    SDL_Rect selCoor;
        selCoor.x    =   coor;
        selCoor.y    =   72;

    SDL_BlitSurface(image,&perFrame,screen,&selCoor);//Rostro activo
}
