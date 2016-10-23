#include <stdio.h>
#include <zlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


typedef struct{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* player;
    SDL_Surface* playerBack;
}GRAPH;

void menuPersonaje(SDL_Surface* screen,SDL_Window* window);//SelecciÃ³n de personaje
    void elementosMenu(SDL_Surface* screen,SDL_Surface* image);
    void animEscotilla(SDL_Surface* screen,SDL_Surface* image);
    void select(SDL_Surface* screen,SDL_Surface* image,int copia,int coor);
void ToggleFullscreen(SDL_Window* window);

void nivel1(SDL_Surface* screen,SDL_Window* window);
void escenario1(SDL_Surface* screen,SDL_Window* window,SDL_Surface* scene);

/**Arrays*/
void clarkStandArr(SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkStandBackArr(SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkRunArr(SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkRunBackArr(SDL_Rect torzo[4],SDL_Rect pierna[4]);
/**Funciones Movimiento*/
void clarkStand(GRAPH g,int *iT,int *iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkRun(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkStandBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkRunBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
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

/**Funciones Arrays*/


void clarkStandArr(SDL_Rect torzo[4],SDL_Rect pierna[1]){
    torzo[0].x=10; torzo[0].y=5;//Parado--------------------------
    torzo[0].w=35; torzo[0].h=35;

    torzo[1].x=43; torzo[1].y=5;
    torzo[1].w=35; torzo[1].h=35;

    torzo[2].x=76; torzo[2].y=5;
    torzo[2].w=35; torzo[2].h=35;

    torzo[3].x=109; torzo[3].y=5;
    torzo[3].w=35; torzo[3].h=35;

    pierna[0].x=145; pierna[0].y=20;
    pierna[0].w=35; pierna[0].h=34;//-----------------------------
}

void clarkStandBackArr(SDL_Rect torzo[4],SDL_Rect pierna[1]){
    torzo[0].x=710; torzo[0].y=5;//Parado--------------------------
    torzo[0].w=30; torzo[0].h=30;

    torzo[1].x=677; torzo[1].y=5;
    torzo[1].w=30; torzo[1].h=30;

    torzo[2].x=644; torzo[2].y=5;
    torzo[2].w=30; torzo[2].h=30;

    torzo[3].x=611; torzo[3].y=5;
    torzo[3].w=30; torzo[3].h=30;

    pierna[0].x=580; pierna[0].y=20;
    pierna[0].w=30; pierna[0].h=30;//-----------------------------
}

void clarkRunArr(SDL_Rect torzo[4],SDL_Rect pierna[6]){
    torzo[0].x=10; torzo[0].y=5;//Parado--------------------------
    torzo[0].w=35; torzo[0].h=35;

    torzo[1].x=43; torzo[1].y=5;
    torzo[1].w=35; torzo[1].h=35;

    torzo[2].x=76; torzo[2].y=5;
    torzo[2].w=35; torzo[2].h=35;

    torzo[3].x=109; torzo[3].y=5;
    torzo[3].w=35; torzo[3].h=35;
            //Corriendo---------------------------------------------------------
    pierna[0].x=13; pierna[0].y=434;
    pierna[0].w=34; pierna[0].h=34;

    pierna[1].x=57; pierna[1].y=434;
    pierna[1].w=34; pierna[1].h=34;

    pierna[2].x=101; pierna[2].y=434;
    pierna[2].w=34;  pierna[2].h=34;

    pierna[3].x=133; pierna[3].y=434;
    pierna[3].w=34;  pierna[3].h=34;

    pierna[4].x=167; pierna[4].y=434;
    pierna[4].w=34;  pierna[4].h=34;

    pierna[5].x=201; pierna[5].y=434;
    pierna[5].w=34;  pierna[5].h=34;//----------------------------
}

void clarkRunBackArr(SDL_Rect torzo[4],SDL_Rect pierna[6]){
    //Parado-------------------------------
    torzo[0].x=710; torzo[0].y=5;
    torzo[0].w=30; torzo[0].h=30;

    torzo[1].x=677; torzo[1].y=5;
    torzo[1].w=30; torzo[1].h=30;

    torzo[2].x=644; torzo[2].y=5;
    torzo[2].w=30; torzo[2].h=30;

    torzo[3].x=611; torzo[3].y=5;
    torzo[3].w=30; torzo[3].h=30;
    //Corriendo---------------------------------------------------------
    pierna[0].x=711; pierna[0].y=434;
    pierna[0].w=34; pierna[0].h=34;

    pierna[1].x=667; pierna[1].y=434;
    pierna[1].w=34; pierna[1].h=34;

    pierna[2].x=626; pierna[2].y=434;
    pierna[2].w=34;  pierna[2].h=34;

    pierna[3].x=591; pierna[3].y=434;
    pierna[3].w=34;  pierna[3].h=34;

    pierna[4].x=557; pierna[4].y=434;
    pierna[4].w=34;  pierna[4].h=34;

    pierna[5].x=523; pierna[5].y=434;
    pierna[5].w=34;  pierna[5].h=34;//----------------------------------
}

/**Funciones movimiento*/
void clarkStand(GRAPH g,int *iT,int *iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
        SDL_Rect torCoor,pierCoor;

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

        if(g.player) {//Manejo de error
            SDL_BlitSurface(g.player,&pierna[0],g.screen,&pierCoor);//Clark piernas
            SDL_BlitSurface(g.player,&torzo[*iT],g.screen,&torCoor);//Clark torzo
            SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
        }else{printf("IMG_Load: %s\n", IMG_GetError());}
}

void clarkStandBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
    SDL_Rect torCoor,pierCoor;

    torCoor.x=2+x; torCoor.y=20+y;//Torzo
    pierCoor.x=9+x; pierCoor.y=41+y;//Piernas

    if(g.player) {//Manejo de error
        SDL_BlitSurface(g.playerBack,&pierna[0],g.screen,&pierCoor);//Clark piernas
        SDL_BlitSurface(g.playerBack,&torzo[iT],g.screen,&torCoor);//Clark torzo
        SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    }else{printf("IMG_Load: %s\n", IMG_GetError());}
}

void clarkRun(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
    SDL_Rect torCoor,pierCoor;

    torCoor.x=2+x; torCoor.y=20+y;//Torzo
    pierCoor.x=0+x; pierCoor.y=41+y;//Piernas

    if(g.player) {//Manejo de error
        printf("%d , %d",iT,iP);
        SDL_BlitSurface(g.player,&pierna[iP],g.screen,&pierCoor);//Clark piernas
        SDL_BlitSurface(g.player,&torzo[0],g.screen,&torCoor);//Clark torzo
        SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    }else{printf("IMG_Load: %s\n", IMG_GetError());}
}

void clarkRunBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
    SDL_Rect torCoor,pierCoor;

    torCoor.x=0+x; torCoor.y=20+y;//Torzo coor
    pierCoor.x=7+x; pierCoor.y=41+y;//Piernas coor

    if(g.player) {//Manejo de error
        SDL_BlitSurface(g.playerBack,&pierna[iP],g.screen,&pierCoor);//Clark piernas
        SDL_BlitSurface(g.playerBack,&torzo[iT],g.screen,&torCoor);//Clark torzo
        SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    }else{printf("IMG_Load: %s\n", IMG_GetError());}
}

void nivel1(SDL_Surface* screen,SDL_Window* window){
    GRAPH g;
    SDL_Event tecla;
    int iT=0,iP=0;
    int a1=0,a2=0;
    int x=100,y=140;
    unsigned int lastTime=0,currentTime=0,deltaTime=0;
    int direccion=0;

    SDL_Surface* scene;
    SDL_Surface* player;
    SDL_Surface* playerBack;

    /**Arrays*/
    SDL_Rect csT[4],csP[1];
    SDL_Rect csbT[4],csbP[1];
    SDL_Rect crT[4],crP[6];
    SDL_Rect crbT[4],crbP[6];
    clarkStandArr(csT,csP);
    clarkStandBackArr(csbT,csbP);
    clarkRunArr(crT,crP);
    clarkRunBackArr(crbT,crbP);

    int flag=IMG_INIT_PNG;//Iniciando soporte png
    IMG_Init(flag);

    scene=IMG_Load("images/mision1.png");//Cargando backgrounds
    player=IMG_Load("images/clark.png");//Cargando jugador
    playerBack=IMG_Load("images/clarkBack.png");//Cargando jugador

    g.window=window;
    g.screen=screen;
    g.player=player;
    g.playerBack=playerBack;

    while(true){
        currentTime = SDL_GetTicks();
        deltaTime=(currentTime-lastTime)/1000.0f;
        if(SDL_PollEvent(&tecla)){//Capturando teclas
            if(tecla.type==SDL_KEYDOWN){
                switch(tecla.key.keysym.sym){//Salir
                    case SDLK_ESCAPE:
                        exit(0);
                    break;
                    case SDLK_RIGHT://Derecha
                        clarkRun(g,iT,iP,x,y,crT,crP);
                        direccion=0;
                        x+=2;
                    break;
                    case SDLK_LEFT://Izquierda
                    clarkRunBack(g,iT,iP,x,y,crbT,crbP);
                    direccion=-1;
                    x-=2;
                    break;
                }
            }
        }
        /**Estas funciones se ejecutan siempre*/
        escenario1(screen,window,scene);
        if(currentTime>lastTime+100){
            iT++; iP++;//Numero de sprite
            if(iP>=6){iP=0;}//Loop de sprite
            if(iT>=4){iT=0;}//Loop de sprite
            if(direccion==0){
                clarkStand(g,&iT,&iP,x,y,csT,csP);
            }else{
                clarkStandBack(g,iT,iP,x,y,csbT,csbP);//
            }
            lastTime = currentTime;//Control de tiempo
        }
    }//while
}

void escenario1(SDL_Surface* screen,SDL_Window* window,SDL_Surface* scene){
    SDL_Rect cielo;
        cielo.x=10; cielo.y=408;
        cielo.w=502; cielo.h=112;
    SDL_Rect tierraLejana;
        tierraLejana.x=10; tierraLejana.y=560;
        tierraLejana.w=502; tierraLejana.h=168;
        SDL_Rect coorTieLej;
            coorTieLej.x=0;
            coorTieLej.y=57;

    SDL_Rect tierra;
        tierra.x=10; tierra.y=10;
        tierra.w=502; tierra.h=250;

    SDL_BlitSurface(scene,&cielo,screen,NULL);
    SDL_BlitSurface(scene,&tierraLejana,screen,&coorTieLej);
    SDL_BlitSurface(scene,&tierra,screen,NULL);
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
