#include <stdio.h>
#include <zlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void menuPersonaje(SDL_Surface* screen,SDL_Window* window);//SelecciÃ³n de personaje
    void elementosMenu(SDL_Surface* screen,SDL_Surface* image);
    void animEscotilla(SDL_Surface* screen,SDL_Surface* image);
    void select(SDL_Surface* screen,SDL_Surface* image,int copia,int coor);
void ToggleFullscreen(SDL_Window* window);

void nivel1(SDL_Surface* screen,SDL_Window* window);
void escenario1(SDL_Surface* screen,SDL_Window* window,SDL_Surface* scene);
void clark(SDL_Surface* screen,SDL_Window* window,SDL_Surface* player,int *iT,int *iP,int x,int y);
void clarkRun(SDL_Surface* screen,SDL_Window* window,SDL_Surface* player,int *iT,int *iP,int x,int y);
//MAIN
int main ( int argc, char** argv ){
    SDL_Window* window=NULL;//Ventana
    SDL_Surface* screen=NULL;//Pantalla

    if(SDL_Init(SDL_INIT_VIDEO)>-1){//Iniciando soporte de video
        window=SDL_CreateWindow("MS",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_SHOWN);//Creando ventana
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

void clark(SDL_Surface* screen, SDL_Window* window,SDL_Surface* player,int *iT,int *iP,int x,int y){
        SDL_Rect torzo[4][1],pierna[1][1],torCoor,pierCoor;
            torzo[0][0].x=10; torzo[0][0].y=5;//Parado--------------------------
            torzo[0][0].w=35; torzo[0][0].h=35;

            torzo[1][0].x=43; torzo[1][0].y=5;
            torzo[1][0].w=35; torzo[1][0].h=35;

            torzo[2][0].x=76; torzo[2][0].y=5;
            torzo[2][0].w=35; torzo[2][0].h=35;

            torzo[3][0].x=109; torzo[3][0].y=5;
            torzo[3][0].w=35; torzo[3][0].h=35;

            pierna[0][0].x=145; pierna[0][0].y=20;
            pierna[0][0].w=35; pierna[0][0].h=34;//-----------------------------

            /*torzo[0][1].x=19; torzo[0][1].y=50;//Disparando adelante------------
            torzo[0][1].w=55; torzo[0][1].h=30;

            torzo[1][1].x=85; torzo[1][1].y=50;
            torzo[1][1].w=55; torzo[1][1].h=30;

            torzo[2][1].x=153; torzo[2][1].y=50;
            torzo[2][1].w=58; torzo[2][1].h=30;

            torzo[3][1].x=206; torzo[3][1].y=50;
            torzo[3][1].w=37; torzo[3][1].h=30;

            torzo[4][1].x=206; torzo[4][1].y=50;
            torzo[4][1].w=50; torzo[4][1].h=30;

            torzo[5][1].x=303; torzo[5][1].y=50;
            torzo[5][1].w=45; torzo[5][1].h=30;

            torzo[6][1].x=352; torzo[6][1].y=50;
            torzo[6][1].w=45; torzo[6][1].h=30;

            torzo[7][1].x=401; torzo[7][1].y=48;
            torzo[7][1].w=40; torzo[7][1].h=30;

            torzo[8][1].x=449; torzo[8][1].y=49;
            torzo[8][1].w=35; torzo[8][1].h=30;

            torzo[9][1].x=498; torzo[9][1].y=50;
            torzo[9][1].w=35; torzo[9][1].h=30;//-------------------------------

            torzo[0][2].x=10; torzo[0][2].y=85;//Apuntando arriba---------------
            torzo[0][2].w=35; torzo[0][2].h=35;

            torzo[1][2].x=43; torzo[1][2].y=85;
            torzo[1][2].w=33; torzo[1][2].h=35;

            torzo[2][2].x=76; torzo[2][2].y=85;
            torzo[2][2].w=35; torzo[2][2].h=35;

            torzo[3][2].x=109; torzo[3][2].y=85;
            torzo[3][2].w=35; torzo[3][2].h=35;//-------------------------------

            //Corregir medidas partir de aqui
            //Necesita variable tAux para compensar altura
            torzo[0][3].x=12; torzo[0][3].y=145;//Disparando arriba-------------
            torzo[0][3].w=23; torzo[0][3].h=45;

            torzo[1][3].x=35; torzo[1][3].y=145;
            torzo[1][3].w=23; torzo[1][3].h=45;

            torzo[2][3].x=65; torzo[2][3].y=145;
            torzo[2][3].w=23; torzo[2][3].h=45;

            torzo[3][3].x=100; torzo[3][3].y=145;
            torzo[3][3].w=23; torzo[3][3].h=45;

            torzo[4][3].x=133; torzo[4][3].y=145;
            torzo[4][3].w=23; torzo[4][3].h=45;

            torzo[5][3].x=165; torzo[5][3].y=145;
            torzo[5][3].w=25; torzo[5][3].h=45;

            torzo[6][3].x=208; torzo[6][3].y=145;
            torzo[6][3].w=25; torzo[6][3].h=45;

            torzo[7][3].x=238; torzo[7][3].y=145;
            torzo[7][3].w=25; torzo[7][3].h=45;

            torzo[8][3].x=273; torzo[8][3].y=145;
            torzo[8][3].w=23; torzo[8][3].h=45;

            torzo[9][3].x=300; torzo[9][3].y=145;
            torzo[9][3].w=23; torzo[9][3].h=45;//-------------------------------

            torzo[0][4].x=10; torzo[0][4].y=200;//Recargando arma-----------------
            torzo[0][4].w=35; torzo[0][4].h=40;

            torzo[1][4].x=45; torzo[1][4].y=200;
            torzo[1][4].w=40; torzo[1][4].h=40;

            torzo[2][4].x=90; torzo[2][4].y=200;
            torzo[2][4].w=40; torzo[2][4].h=40;

            torzo[3][4].x=135; torzo[3][4].y=200;
            torzo[3][4].w=40; torzo[3][4].h=40;

            torzo[4][4].x=190; torzo[4][4].y=200;
            torzo[4][4].w=40; torzo[4][4].h=40;

            torzo[5][4].x=245; torzo[5][4].y=200;
            torzo[5][4].w=40; torzo[5][4].h=40;

            torzo[6][4].x=295; torzo[6][4].y=200;
            torzo[6][4].w=40; torzo[6][4].h=40;//-----------------------------*/

            torCoor.x=2+x; torCoor.y=20+y;//Torzo
            pierCoor.x=0+x; pierCoor.y=41+y;//Piernas

        if(player) {//Manejo de error
            if(*iT==4)
                *iT=0;
            //if(*iP==6)
              //  *iP=0;
            SDL_BlitSurface(player,&pierna[0][0],screen,&pierCoor);//Clark piernas
            SDL_BlitSurface(player,&torzo[*iT][0],screen,&torCoor);//Clark torzo
            SDL_UpdateWindowSurface(window);//Refrescando pantalla
        }else{printf("IMG_Load: %s\n", IMG_GetError());}
}
/**Funciona pero va demasiado rápido. Necesita ajustes de tiempo*/
void clarkRun(SDL_Surface* screen, SDL_Window* window,SDL_Surface* player,int *iT,int *iP,int x,int y){
        SDL_Rect torzo[4][1],pierna[6][1],torCoor,pierCoor;
            torzo[0][0].x=10; torzo[0][0].y=5;//Parado--------------------------
            torzo[0][0].w=35; torzo[0][0].h=35;

            torzo[1][0].x=43; torzo[1][0].y=5;
            torzo[1][0].w=35; torzo[1][0].h=35;

            torzo[2][0].x=76; torzo[2][0].y=5;
            torzo[2][0].w=35; torzo[2][0].h=35;

            torzo[3][0].x=109; torzo[3][0].y=5;
            torzo[3][0].w=35; torzo[3][0].h=35;
            //Corriendo---------------------------------------------------------
            pierna[0][0].x=13; pierna[0][0].y=434;
            pierna[0][0].w=35; pierna[0][0].h=34;

            pierna[1][0].x=57; pierna[1][0].y=434;
            pierna[1][0].w=35; pierna[1][0].h=34;

            pierna[2][0].x=101; pierna[2][0].y=434;
            pierna[2][0].w=35;  pierna[2][0].h=34;

            pierna[3][0].x=133; pierna[3][0].y=434;
            pierna[3][0].w=35;  pierna[3][0].h=34;

            pierna[4][0].x=167; pierna[4][0].y=434;
            pierna[4][0].w=35;  pierna[4][0].h=34;

            pierna[5][0].x=201; pierna[5][0].y=434;
            pierna[5][0].w=35;  pierna[5][0].h=34;//----------------------------

            torCoor.x=2+x; torCoor.y=20+y;//Torzo
            pierCoor.x=0+x; pierCoor.y=41+y;//Piernas

        if(player) {//Manejo de error
            if(*iT>=4){
                *iT=0;
            }
            if(*iP>=6){
                *iP=0;
            }
            SDL_BlitSurface(player,&pierna[*iP][0],screen,&pierCoor);//Clark piernas
            SDL_BlitSurface(player,&torzo[*iT][0],screen,&torCoor);//Clark torzo
            SDL_UpdateWindowSurface(window);//Refrescando pantalla
        }else{printf("IMG_Load: %s\n", IMG_GetError());}
}

void nivel1(SDL_Surface* screen,SDL_Window* window){
    SDL_Event tecla;
    int *iT,*iP;
    int a1=0,a2=0;
    int x=100,y=140;
    iT=&a1;
    iP=&a2;
    unsigned int lastTime=0,currentTime;

    SDL_Surface* scene;
    SDL_Surface* player;
    int flag=IMG_INIT_PNG;//Iniciando soporte png
    IMG_Init(flag);

    scene=IMG_Load("mision1.png");//Cargando backgrounds
    player=IMG_Load("clark.png");//Cargando jugador

    while(true){
        if(SDL_PollEvent(&tecla)){//Capturando teclas
            if(tecla.type==SDL_QUIT)
                exit(0);
            else
            if(tecla.type==SDL_KEYDOWN){
                if(tecla.key.keysym.sym==SDLK_ESCAPE)//Salir
                    exit(0);
                else if(tecla.key.keysym.sym==SDLK_RIGHT){//Derecha
                    clarkRun(screen,window,player,iT,iP,x,y);
                    x+=5;
                }
                else if(tecla.key.keysym.sym==SDLK_LEFT){//Izquierda
                    x-=5;
                }
                else if(tecla.key.keysym.sym==SDLK_f){//Pantalla completa

                }
            }
        }else{
            /**Si no se oprime ninguna tecla se ejecutan las siguientes funciones*/
            clark(screen,window,player,iT,iP,x,y);

        }
        /**Estas funciones se ejecutan siempre*/
        escenario1(screen,window,scene);
        currentTime = SDL_GetTicks();
        if(currentTime > lastTime + 400){
            (*iT)++; (*iP)++;
            lastTime = currentTime;
        }
    }//while
}

void escenario1(SDL_Surface* screen,SDL_Window* window,SDL_Surface* scene){
    SDL_BlitSurface(scene,NULL,screen,NULL);
}

void menuPersonaje(SDL_Surface* screen,SDL_Window* window){//Funcion para elegir personaje
    SDL_Surface* image=NULL;//Puntero a imagen
    SDL_Event tecla;
    int arr[4],copia[4],i=0;

    int flag=IMG_INIT_PNG;//Iniciando soporte PNG
    IMG_Init(flag);//Iniciando soporte IMG

    if((IMG_Init(flag)&flag)){//Manejo de error
        image=IMG_Load("select.png");//Cargando imagen
        if(image) {//Manejo de error
            copia[0]=309; copia[1]=374;//Coordenadas de sector copiado
            copia[2]=441; copia[3]=508;

            arr[0]=18;  arr[1]=83;//Coordenadas de inserciÃ³n de copia
            arr[2]=150; arr[3]=217;

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
                animEscotilla(screen,image);
                elementosMenu(screen,image);
                select(screen,image,copia[i],arr[i]);
                SDL_UpdateWindowSurface(window);//Refrescando pantalla
            }
        }else{printf("IMG_Load: %s\n", IMG_GetError());}
    }else{
        printf("Error IMG_Init %s",IMG_GetError());
    }
}//******************

void ToggleFullscreen(SDL_Window* window){
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    int res;

    res=SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
    if(res==0)
        printf("Succes!");
    else
        printf("Error");
    SDL_ShowCursor(IsFullscreen);
}

void elementosMenu(SDL_Surface* screen, SDL_Surface* image){
    SDL_Rect frame;//Marco de seleccion
        frame.x=4;
        frame.y=107;
        frame.w=305;
        frame.h=223;
    SDL_Rect marF;//Mostrando rostros inactivos
        marF.x=309; marF.y=3;
        marF.w=364; marF.h=121;
    SDL_Rect marC;
        marC.x=18;
        marC.y=73;

    SDL_BlitSurface(image,&frame,screen,NULL);//Marco
    SDL_BlitSurface(image,&marF,screen,&marC);//Rostros inactivos
}

void animEscotilla(SDL_Surface* screen,SDL_Surface* image){
    SDL_Rect door;//Escotilla
        door.x=0;  door.y=335;
        door.w=68; door.h=134;
    SDL_Rect coorDoor;
        coorDoor.x=12;
        coorDoor.y=63;

    SDL_BlitSurface(image,&door,screen,&coorDoor);//Escotilla
}

void select(SDL_Surface* screen,SDL_Surface* image,int copia,int coor){
    SDL_Rect perFrame;//Seleccion
        perFrame.x=copia; perFrame.y=125;
        perFrame.w=68;  perFrame.h=122;

    SDL_Rect selCoor;
        selCoor.x=coor;
        selCoor.y=72;

    SDL_BlitSurface(image,&perFrame,screen,&selCoor);//Rostro activo
}
