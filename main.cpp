#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_image.h>
#include "floor.h"
#include "animation.h"

void menuPersonaje(    SDL_Surface* screen,SDL_Window*  window);//SelecciÃ³n de personaje
    void elementosMenu(SDL_Surface* screen,SDL_Surface* image);
    void animEscotilla(SDL_Surface* screen,SDL_Surface* image);
    void select(       SDL_Surface* screen,SDL_Surface* image,int copia,int coor);

void nivel1(           SDL_Surface* screen,SDL_Window*  window);
void escenario1(       SCENE scene);

//MAIN
int main ( int argc, char** argv ){
    SDL_Window*    window  =  NULL;//Ventana
    SDL_Surface*   screen  =  NULL;//Pantalla

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)>-1){//Iniciando soporte de video
        window=SDL_CreateWindow("Metal Slug",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,502,238,SDL_WINDOW_SHOWN);//Creando ventana
        if(window){//Manejo de error
            screen=SDL_GetWindowSurface(window);//Creando pantalla

            //menuPersonaje(screen,window);//Seleccion de personaje
            nivel1(screen,window);

        }else{
            printf("Error SDL_CreateWindow %s",SDL_GetError());
        }
    }else{
        printf("Error SDL_Init %s",SDL_GetError());
    }
    SDL_DestroyWindow(window);//Cerrando ventana
    IMG_Quit();
    SDL_Quit();//Cerrando SDL
    return 0;
}//MAIN

void nivel1(SDL_Surface* screen,SDL_Window* window){
    GRAPH g;
    SCENE move;
    int iT       =    0;
    int iP       =    0;
    int iS       =    0;
    int iShoot   =    0;//Index de disparo
    int x        =  -20;//Posición mínima en x
    int h        =    0;//Indice de arreglo altura
    unsigned int pastBreath  =   0,currentBreath;
    unsigned int pastWalk    =   0,currentWalk;
    unsigned int pastJump    =   0,currentJump;
    unsigned int pastShoot   =   0,currentShoot;

    SDL_Surface* scene;
    SDL_Surface* player;
    SDL_Surface* playerBack;

    /**Array declaration*/
    SDL_Rect csT[     4],     csP[1];//clarkStan array
    SDL_Rect csbT[    4],    csbP[1];//clarkStandBack array
    SDL_Rect crT[     4],     crP[6];//clarkRun arr
    SDL_Rect crbT[    4],    crbP[6];//clarkRunBack arr
    SDL_Rect cshT[    9];
    int piso[       519];
    int salto[       51];

    /**Array definition*/
    clarkStandArr(         csT   ,  csP    );
    clarkStandBackArr(     csbT  ,  csbP   );
    clarkRunArr(           crT   ,  crP    );
    clarkRunBackArr(       crbT  ,  crbP   );
    clarkShootArr(         cshT            );

    altura(piso);
    clarkJump(salto);

    int flag=IMG_INIT_PNG;//Iniciando soporte png
    IMG_Init(flag);

    scene=IMG_Load(         "images/mision1.png"     );//Cargando backgrounds
    player=IMG_Load(        "images/clark.png"       );//Cargando jugador
    playerBack=IMG_Load(    "images/clarkBack.png"   );//Cargando jugador

    g.window          =     window;
    g.screen          =     screen;
    g.player          =     player;
    g.playerBack      =     playerBack;

    move.window       =     window;
    move.screen       =     screen;
    move.scene        =     scene;
    move.x            =     0;
    move.xMountain    =     0;
    move.xHorizon     =     0;

    int direccion     =     1;
    int direccionAux  =     0;
    bool key_left     =     false;
    bool key_right    =     false;
    bool key_down     =     false;
    bool key_up       =     false;
    bool walk         =     false;
    bool jump         =     false;
    bool keepWalking  =     false;
    bool jumpArr      =     false;
    bool breath       =     false;
    bool shoot        =     false;
    bool key_shoot    =     false;


    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,"1");

    SDL_Event               tecla;
    SDL_Joystick         *  joy;
    SDL_GameController   *  controller;
    int boton;
    int mouse;
    int focus;

    if (controller) {
        int control = SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
        if(control >= 0){
            controller = SDL_GameControllerOpen(0);
            joy = SDL_GameControllerGetJoystick(controller);
            if(SDL_NumJoysticks() > 0){
                printf("Joystick detected\n");
                joy = SDL_JoystickOpen(0);
                if(joy){
                    printf("Joystick listo: %s\n",SDL_JoystickName(joy));
                }else{
                    printf("Joystick error %s\n",SDL_GetError());
                }
            }else{
                printf("No hay Joysticks disponibles\n");
                free(joy);
                free(controller);
            }
        }else{
            printf("%s\n",SDL_GetError());
        }
    }else{
        printf("Error %s\n",SDL_GetError());
    }

    while(true){
        if(SDL_PollEvent(&tecla)){//Capturando teclas
            if(tecla.type==SDL_KEYDOWN){//Presionando tecla
                if(tecla.key.keysym.sym == SDLK_RIGHT){//Derecha
                        key_right     =   true;
                        direccionAux  =   1;//
                        direccion     =   1;
                }else if( tecla.key.keysym.sym == SDLK_LEFT){//Izquierda
                        key_left      =   true;
                        direccionAux  =  -1;
                        direccion     =  -1;//Dirección izquierda
                }else if(tecla.key.keysym.sym == SDLK_ESCAPE){
                    exit(0);
                }
                if(tecla.key.keysym.sym == SDLK_s)//Saltando
                        jump      = true;
                if(tecla.key.keysym.sym == SDLK_x){//Disparando
                    key_shoot     =   true;
                    iShoot        =   3;
                }
            }
            if(tecla.type==SDL_KEYUP){//Soltando tecla
                if(tecla.key.keysym.sym == SDLK_RIGHT)//Derecha
                    key_right     =  false;

                else if(tecla.key.keysym.sym == SDLK_LEFT)//Izquierda
                    key_left      =  false;

                if(!jump)
                    direccionAux  =  0;//Auxiliar de dirección en salto y disparo
            }
            if(tecla.type == SDL_QUIT){
                exit(0);//cerrando
            }
            //Joystick =============================
            if(tecla.type == SDL_JOYBUTTONDOWN){
                if(tecla.jbutton.button == 2){
                    jump      =  true;
                }
                if(tecla.jbutton.button == 5){
                    key_shoot =  true;
                    iShoot    =  3;
                }
            }
            //if(tecla.type == SDL_JOYBUTTONUP){
            //    if(tecla.jbutton.button == 3){
            //            shoot = false;
            //    }
            //}
            if(tecla.type == SDL_JOYAXISMOTION){
                if(tecla.jaxis.axis      == 0){
                    if(tecla.jaxis.value == 0){//Sin movimiento
                        key_right      =   false;
                        key_left       =   false;
                        if(!jump)
                            direccionAux  =  0;
                    }
                    else if(tecla.jaxis.value > 0){//Derecha
                        key_right      =   true;
                        direccion      =   1;//Dirección gral
                        direccionAux   =   1;//Dirección salto
                        keepWalking    =   true;
                    }
                    else if(tecla.jaxis.value < 0){
                        key_left       =   true;
                        direccion      =  -1;//Dirección izquierda
                        direccionAux   =  -1;
                        keepWalking    =   true;
                    }
                }
            }
            //Termina Joystick======================================
        }

        /***Acciones de eventos */
        if(key_right || (jump && keepWalking && direccionAux == 1)){
            //Si se dispara o salta se desactiva este sprite
            if(!jump)
                clarkRun(g,iT,iP,x,piso[h],crT,crP);

                if(x<400){
                    x++;//Moviendonos horizontalmente
                }else{
                    move.x++;/**Trabajando*/
                }
                if(h < 519){//Límite de arreglo
                    h++;//Arreglo de altura
                }
        }else if(key_left || (jump && keepWalking && direccionAux == -1)){
            if(!jump)
                clarkRunBack(g,iT,iP,x,piso[h],crbT,crbP);
                if(h > 0){
                    x--;//Retrocediendo
                    if(move.x < 220)
                        h--;//Arreglo de altura
                }
        }else{//Default
            if(!jump && !key_shoot){
                if(direccion==1){
                    clarkStand(     g,&iT,&iP,x,piso[h],csT,csP);
                }else if(direccion == -1){
                    clarkStandBack( g,iT,iP,x,piso[h],csbT,csbP);//
                }
            }
        }
        if(key_shoot){
            clarkPier(              g,x,piso[h]-salto[iS],csP);
            clarkShoot(             g,&iT,x,piso[h]-salto[iS],cshT);
        }
        if(jump){//SALTANDO
            if(direccion==1){
                clarkStand(         g,&iT,&iP,x,piso[h]-salto[iS],csT,csP);
                //x++; h++;
            }else{
                clarkStandBack(     g,iT,iP,x,piso[h]-salto[iS],csbT,csbP);//
                //x--; h--;
            }
            if(jumpArr)
                iS++;//indice array salto
            if(iS>=51){//Límite de array salto
                jump           =   false;//Términa salto
                keepWalking    =   false;
                direccionAux   =   0;
                iS = 0;//Reiniciando indice
            }
            if(iS <= 51)
                keepWalking    =   true;
        }
        /*Estas funciones se ejecutan siempre*/
        escenario1(move);

        if(breath){
            iT++;// Torzo
        }
        if(walk){
            iP++;// Pies
        }
        if(shoot && key_shoot){
            iShoot++;
        }

        if( iP>=6      ){ iP=0;                 }//Loop de sprite
        if( iT>=4      ){ iT=0;                 }//Loop de sprite
        if( iShoot>=9  ){ iShoot=0;
                          key_shoot=false;      }

        breath       = false;
        walk         = false;
        jumpArr      = false;
        shoot        = false;

        /**Funciones de tiempo*/
        currentBreath     =    SDL_GetTicks();
        currentWalk       =    SDL_GetTicks();
        currentJump       =    SDL_GetTicks();
        currentShoot      =    SDL_GetTicks();

        if(currentBreath  >    pastBreath+200){
            breath        =    true;
            pastBreath    =    currentBreath;
        }
        if(currentWalk    >    pastWalk + 100){
            walk          =    true;
            pastWalk      =    currentWalk;
        }
        if(currentJump    >    pastJump + 10){
            jumpArr       =    true;
            pastJump      =    currentJump;
        }
        if(currentShoot   >    pastShoot + 20){
            shoot         =    true;
            pastShoot     =    currentShoot;
        }
        /*Funciones de tiempo**/
    }//while

    if (SDL_JoystickGetAttached(joy)) {
        SDL_JoystickClose(joy);
    }

}

void clarkJump(int salto[]){
    salto[0 ]    =    0 ;
    salto[1 ]    =    4 ;
    salto[2 ]    =    8 ;
    salto[3 ]    =    13;
    salto[4 ]    =    18;
    salto[5 ]    =    22;
    salto[6 ]    =    26;
    salto[7 ]    =    29;
    salto[8 ]    =    32;
    salto[9 ]    =    35;
    salto[10]    =    38;
    salto[11]    =    41;
    salto[12]    =    43;
    salto[13]    =    45;
    salto[14]    =    47;
    salto[15]    =    49;
    salto[16]    =    51;
    salto[17]    =    52;
    salto[18]    =    53;
    salto[19]    =    54;
    salto[20]    =    55;
    salto[21]    =    56;
    salto[22]    =    57;
    salto[23]    =    58;
    salto[24]    =    59;
    salto[25]    =    59;/////

    salto[26]    =    59;
    salto[27]    =    59;
    salto[28]    =    58;
    salto[29]    =    57;
    salto[30]    =    56;
    salto[31]    =    55;
    salto[32]    =    54;
    salto[33]    =    53;
    salto[34]    =    52;
    salto[35]    =    51;
    salto[36]    =    49;
    salto[37]    =    47;
    salto[38]    =    45;
    salto[39]    =    43;
    salto[40]    =    40;
    salto[41]    =    37;
    salto[42]    =    34;
    salto[43]    =    31;
    salto[44]    =    28;
    salto[45]    =    25;
    salto[46]    =    21;
    salto[47]    =    17;
    salto[48]    =    12;
    salto[49]    =    8 ;
    salto[50]    =    4 ;
    salto[51]    =    0 ;
}
/**
    x coor x de suelo
    xMountan coor x de montañas
    xHorizon coor x de el horizonte
*/
void escenario1(SCENE move){
    SDL_Rect cielo;
        cielo.x           =  10+move.xHorizon ;  cielo.y         =   408;
        cielo.w           =  502+move.xHorizon;  cielo.h         =   112;
    SDL_Rect tierraLejana;
        tierraLejana.x    =  10+move.xMountain;  tierraLejana.y  =   560;
        tierraLejana.w    =  502+move.xMountain; tierraLejana.h  =   168;
    SDL_Rect coorTieLej;
        coorTieLej.x      =  0 ;
        coorTieLej.y      =  57;

    SDL_Rect tierra;
        tierra.x          =  10+move.x ;         tierra.y        =   10;
        tierra.w          =  502+move.x;         tierra.h        =   250;

    SDL_BlitSurface(move.scene,&cielo,move.screen,  NULL);
    SDL_BlitSurface(move.scene,&tierraLejana,move.screen,&coorTieLej);
    SDL_BlitSurface(move.scene,&tierra,move.screen, NULL);
}

void menuPersonaje(SDL_Surface* screen,SDL_Window* window){//Funcion para elegir personaje
    SDL_Surface* image=NULL;//Puntero a imagen
    SDL_Event tecla;
    int arr[4],copia[4],i=0;

    int flag=IMG_INIT_PNG;//Iniciando soporte PNG
    IMG_Init(flag);//Iniciando soporte IMG

    if((IMG_Init(flag)&flag)){//Manejo de error
        image=IMG_Load("images/select.png");//Cargando imagen
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
                            ToggleFullscreen(window);//Necesita trabajo
                        }
                    }
                }
                animEscotilla( screen,image);
                elementosMenu( screen,image);
                select(        screen,image,copia[i],arr[i]);
                SDL_UpdateWindowSurface(window);//Refrescando pantalla
            }
        }else{printf("IMG_Load: %s\n", IMG_GetError());}
    }else{
        printf("Error IMG_Init %s",IMG_GetError());
    }
}//******************

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
