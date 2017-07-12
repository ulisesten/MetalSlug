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
//Escenarios
typedef struct{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* scene;
    int x;
    int xMountain;
    int xHorizon;
}SCENE;

void menuPersonaje(SDL_Surface* screen,SDL_Window* window);//SelecciÃ³n de personaje
    void elementosMenu(SDL_Surface* screen,SDL_Surface* image);
    void animEscotilla(SDL_Surface* screen,SDL_Surface* image);
    void select(SDL_Surface* screen,SDL_Surface* image,int copia,int coor);
void ToggleFullscreen(SDL_Window* window,SDL_Surface* screen);

void nivel1(SDL_Surface* screen,SDL_Window* window);
void escenario1(SCENE scene);

/**Arrays*/
void clarkStandArr(SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkStandBackArr(SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkRunArr(SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkRunBackArr(SDL_Rect torzo[4],SDL_Rect pierna[4]);
void clarkJump(int piso[]);
/**Funciones Movimiento*/
void clarkStand(GRAPH g,int *iT,int *iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkRun(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkStandBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);
void clarkRunBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]);

void altura(int piso[]);
//MAIN
int main ( int argc, char** argv ){
    SDL_Window* window=NULL;//Ventana
    SDL_Surface* screen=NULL;//Pantalla

    if(SDL_Init(SDL_INIT_VIDEO)>-1){//Iniciando soporte de video
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
        //printf("%d , %d",iT,iP);
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

void ToggleFullscreen(SDL_Window* window,SDL_Surface* screen){
    //int flags = SDL_BASE_FLAGS | (sdl->window_fullscreen ? SDL_FULLSCREEN : 0);
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    screen=SDL_GetWindowSurface(window);

    int res=SDL_SetWindowFullscreen(window,IsFullscreen);
    if(res==0){
        printf("Succes! %s\n",SDL_GetError());
    }else{
        printf("Error");
    }
    SDL_ShowCursor(IsFullscreen);
}

void nivel1(SDL_Surface* screen,SDL_Window* window){
    GRAPH g;
    SCENE move;
    SDL_Event tecla;
    int iT=0,iP=0,iS=0;
    int x=-20;//Posición mínima en x
    int h=0;//Indice de arreglo altura
    unsigned int lastTime=0,currentTime=0,deltaTime=0;
    int direccion=0;

    SDL_Surface* scene;
    SDL_Surface* player;
    SDL_Surface* playerBack;

    /**Array declaration*/
    SDL_Rect csT[4],csP[1];//clarkStan array
    SDL_Rect csbT[4],csbP[1];//clarkStandBack array
    SDL_Rect crT[4],crP[6];//clarkRun arr
    SDL_Rect crbT[4],crbP[6];//clarkRunBack arr
    int piso[519];
    int salto[51];

    /**Array definition*/
    clarkStandArr(csT,csP);
    clarkStandBackArr(csbT,csbP);
    clarkRunArr(crT,crP);
    clarkRunBackArr(crbT,crbP);

    altura(piso);
    clarkJump(salto);

    int flag=IMG_INIT_PNG;//Iniciando soporte png
    IMG_Init(flag);

    scene=IMG_Load("images/mision1.png");//Cargando backgrounds
    player=IMG_Load("images/clark.png");//Cargando jugador
    playerBack=IMG_Load("images/clarkBack.png");//Cargando jugador

    g.window=window;
    g.screen=screen;
    g.player=player;
    g.playerBack=playerBack;

    move.window=window;
    move.screen=screen;
    move.scene=scene;
    move.x=0;
    move.xMountain=0;
    move.xHorizon=0;

    bool key_left = false;
    bool key_right = false;
    bool key_down = false;
    bool key_up = false;
    bool jump = false;

    while(true){
        currentTime = SDL_GetTicks();
        deltaTime=(currentTime-lastTime)/50000.0f;//control de tiempo
        if(SDL_PollEvent(&tecla)){//Capturando teclas
            if(tecla.type == SDL_QUIT){
                exit(0);//cerrando
            }
            if(tecla.type==SDL_KEYDOWN){//Presionando tecla
                switch(tecla.key.keysym.sym){//Salir
                    case SDLK_RIGHT://Derecha
                        key_right = true;
                    break;
                    case SDLK_LEFT://Izquierda
                        key_left = true;
                    break;
                    case SDLK_f://Pantalla completa
                        ToggleFullscreen(g.window,g.screen);//Necesita trabajo
                    break;
                    case SDLK_s:
                        jump = true;
                    break;
                }
            }
            if(tecla.type==SDL_KEYUP){//Soltando tecla
                switch(tecla.key.keysym.sym){//Salir
                    case SDLK_RIGHT://Derecha
                        key_right = false;
                    break;
                    case SDLK_LEFT://Izquierda
                        key_left = false;
                    break;
                }
            }
        }
        /***Acciones de eventos */
        if(key_right){
            if(!jump) clarkRun(g,iT,iP,x,piso[h],crT,crP);
            direccion=0;
            if(currentTime>lastTime+50){
                if(x<400){
                    x++;//Moviendonos horizontalmente
                }else{
                    move.x++;/**Trabajando*/
                }
                if(h < 519){//Límite de arreglo
                    h++;//Arreglo de altura
                }
            }
            //printf("%d\n",h);
        }else if(key_left){
            if(!jump) clarkRunBack(g,iT,iP,x,piso[h],crbT,crbP);
            direccion=-1;//Dirección del jugador izquierda/derecha
            if(currentTime>lastTime+50){
                if(h > 0){
                    x--;//Retrocediendo
                    h--;//Arreglo de altura
                }
            }
        }else{
            if(!jump){
                if(direccion==0){
                    clarkStand(g,&iT,&iP,x,piso[h],csT,csP);
                }else{
                    clarkStandBack(g,iT,iP,x,piso[h],csbT,csbP);//
                }
            }
        }

        if(jump){//SALTANDO
            if(currentTime>lastTime+50){
            if(direccion==0){
                clarkStand(g,&iT,&iP,x,piso[h]-salto[iS],csT,csP);
                //x++; h++;
            }else{
                clarkStandBack(g,iT,iP,x,piso[h]-salto[iS],csbT,csbP);//
                //x--; h--;
            }
            iS++;//indice array salto
            if(iS>=51){//Límite de array salto
                jump = false;//Términa salto
                iS = 0;//Reiniciando indice
            }
            }
        }
        /**Estas funciones se ejecutan siempre*/
        escenario1(move);
        if(currentTime>lastTime+100){
            iT++; iP++;//Numero de sprite
            if(iP>=6){iP=0;}//Loop de sprite
            if(iT>=4){iT=0;}//Loop de sprite
            lastTime = currentTime;//Control de tiempo
        }
    }//while
}

void clarkJump(int salto[]){
    salto[0]=0;
    salto[1]=4;
    salto[2]=8;
    salto[3]=12;
    salto[4]=17;
    salto[5]=21;
    salto[6]=25;
    salto[7]=28;
    salto[8]=31;
    salto[9]=34;
    salto[10]=37;
    salto[11]=40;
    salto[12]=43;
    salto[13]=45;
    salto[14]=47;
    salto[15]=49;
    salto[16]=51;
    salto[17]=52;
    salto[18]=53;
    salto[19]=54;
    salto[20]=55;
    salto[21]=56;
    salto[22]=57;
    salto[23]=58;
    salto[24]=59;
    salto[25]=59;/////

    salto[26]=59;
    salto[27]=59;
    salto[28]=58;
    salto[29]=57;
    salto[30]=56;
    salto[31]=55;
    salto[32]=54;
    salto[33]=53;
    salto[34]=52;
    salto[35]=51;
    salto[36]=49;
    salto[37]=47;
    salto[38]=45;
    salto[39]=43;
    salto[40]=40;
    salto[41]=37;
    salto[42]=34;
    salto[43]=31;
    salto[44]=28;
    salto[45]=25;
    salto[46]=21;
    salto[47]=17;
    salto[48]=12;
    salto[49]=8;
    salto[50]=4;
    salto[51]=0;
}

void altura(int piso[]){
piso[  0]=128;
piso[  1]=128;
piso[  2]=128;
piso[  3]=128;
piso[  4]=128;
piso[  5]=128;
piso[  6]=128;
piso[  7]=128;
piso[  8]=128;
piso[  9]=128;
piso[ 10]=128;
piso[ 11]=127;
piso[ 12]=127;
piso[ 13]=127;
piso[ 14]=127;
piso[ 15]=127;
piso[ 16]=126;
piso[ 17]=126;
piso[ 18]=126;
piso[ 19]=126;
piso[ 20]=126;
piso[ 21]=125;
piso[ 22]=125;
piso[ 23]=125;
piso[ 24]=125;
piso[ 25]=125;
piso[ 26]=124;
piso[ 27]=124;
piso[ 28]=124;
piso[ 29]=124;
piso[ 30]=124;
piso[ 31]=123;
piso[ 32]=123;
piso[ 33]=123;
piso[ 34]=123;
piso[ 35]=123;
piso[ 36]=122;
piso[ 37]=122;
piso[ 38]=122;
piso[ 39]=122;
piso[ 40]=122;
piso[ 41]=121;
piso[ 42]=121;
piso[ 43]=121;
piso[ 44]=121;
piso[ 45]=121;
piso[ 46]=120;
piso[ 47]=120;
piso[ 48]=120;
piso[ 49]=120;
piso[ 50]=120;
piso[ 51]=119;
piso[ 52]=119;
piso[ 53]=119;
piso[ 54]=119;
piso[ 55]=119;
piso[ 56]=118;
piso[ 57]=118;
piso[ 58]=118;
piso[ 59]=118;
piso[ 60]=118;
piso[ 61]=117;
piso[ 62]=117;
piso[ 63]=117;
piso[ 64]=117;
piso[ 65]=117;
piso[ 66]=116;
piso[ 67]=116;
piso[ 68]=116;
piso[ 69]=116;
piso[ 70]=116;
piso[ 71]=115;
piso[ 72]=115;
piso[ 73]=115;
piso[ 74]=115;
piso[ 75]=115;
piso[ 76]=114;
piso[ 77]=114;
piso[ 78]=114;
piso[ 79]=114;
piso[ 80]=114;
piso[ 81]=113;
piso[ 82]=113;
piso[ 83]=113;
piso[ 84]=113;
piso[ 85]=113;
piso[ 86]=112;
piso[ 87]=112;
piso[ 88]=112;
piso[ 89]=112;
piso[ 90]=112;
piso[ 91]=111;
piso[ 92]=111;
piso[ 93]=111;
piso[ 94]=111;
piso[ 95]=111;
piso[ 96]=110;
piso[ 97]=110;
piso[ 98]=110;
piso[ 99]=110;
piso[100]=110;
piso[101]=109;
piso[102]=109;
piso[103]=109;
piso[104]=109;
piso[105]=109;
piso[106]=108;
piso[107]=108;
piso[108]=108;
piso[109]=108;
piso[110]=108;
piso[111]=107;
piso[112]=107;
piso[113]=107;
piso[114]=107;
piso[115]=106;
piso[116]=106;
piso[117]=106;
piso[118]=106;
piso[119]=106;
piso[120]=105;
piso[121]=105;
piso[122]=105;
piso[123]=105;
piso[124]=105;
piso[125]=105;
piso[126]=104;
piso[127]=104;
piso[128]=104;
piso[129]=104;
piso[130]=104;
piso[131]=104;
piso[132]=103;
piso[133]=103;
piso[134]=103;
piso[135]=103;
piso[136]=103;
piso[137]=103;
piso[138]=102;
piso[139]=102;
piso[140]=102;
piso[141]=102;
piso[142]=102;
piso[143]=102;
piso[144]=101;
piso[145]=101;
piso[146]=101;
piso[147]=101;
piso[148]=101;
piso[149]=101;
piso[150]=102;
piso[151]=102;
piso[152]=104;
piso[153]=104;
piso[154]=104;
piso[155]=104;
piso[156]=105;
piso[157]=105;
piso[158]=105;
piso[159]=105;
piso[160]=105;
piso[161]=105;
piso[162]=106;
piso[163]=106;
piso[164]=106;
piso[165]=106;
piso[166]=107;
piso[167]=107;
piso[168]=107;
piso[169]=107;
piso[170]=107;
piso[171]=107;
piso[172]=108;
piso[173]=108;
piso[174]=108;
piso[175]=108;
piso[176]=108;
piso[177]=108;
piso[178]=109;
piso[179]=109;
piso[180]=109;
piso[181]=109;
piso[182]=109;
piso[183]=109;
piso[184]=110;
piso[185]=110;
piso[186]=110;
piso[187]=110;
piso[188]=110;
piso[189]=110;
piso[190]=111;
piso[191]=111;
piso[192]=111;
piso[193]=111;
piso[194]=111;
piso[195]=111;
piso[196]=112;
piso[197]=112;
piso[198]=112;
piso[199]=112;
piso[200]=112;
piso[201]=112;
piso[202]=113;
piso[203]=113;
piso[204]=113;
piso[205]=113;
piso[206]=114;
piso[207]=114;
piso[208]=114;
piso[209]=114;
piso[210]=115;
piso[211]=115;
piso[212]=115;
piso[213]=115;
piso[214]=116;
piso[215]=116;
piso[216]=116;
piso[217]=116;
piso[218]=117;
piso[219]=117;
piso[220]=117;
piso[221]=117;
piso[222]=118;
piso[223]=118;
piso[224]=118;
piso[225]=118;
piso[226]=119;
piso[227]=119;
piso[228]=119;
piso[229]=119;
piso[230]=120;
piso[231]=120;
piso[232]=120;
piso[233]=120;
piso[234]=120;
piso[235]=120;
piso[236]=121;
piso[237]=121;
piso[238]=121;
piso[239]=121;
piso[240]=121;
piso[241]=121;
piso[242]=122;
piso[243]=122;
piso[244]=122;
piso[245]=122;
piso[246]=123;
piso[247]=123;
piso[248]=123;
piso[249]=123;
piso[250]=124;
piso[251]=124;
piso[252]=124;
piso[253]=124;
piso[254]=125;
piso[255]=125;
piso[256]=125;
piso[257]=125;
piso[258]=125;
piso[259]=125;
piso[260]=126;
piso[261]=126;
piso[262]=126;
piso[263]=126;
piso[264]=126;
piso[265]=126;
piso[266]=127;
piso[267]=127;
piso[268]=127;
piso[269]=127;
piso[270]=127;
piso[271]=127;
piso[272]=128;
piso[273]=128;
piso[274]=128;
piso[275]=128;
piso[276]=128;
piso[277]=128;
piso[278]=129;
piso[279]=129;
piso[280]=129;
piso[281]=129;
piso[282]=129;
piso[283]=129;
piso[284]=130;
piso[285]=130;
piso[286]=130;
piso[287]=130;
piso[288]=130;
piso[289]=130;
piso[290]=131;
piso[291]=131;
piso[292]=131;
piso[293]=131;
piso[294]=131;
piso[295]=131;
piso[296]=132;
piso[297]=132;
piso[298]=132;
piso[299]=132;
piso[300]=132;
piso[301]=132;
piso[302]=132;
piso[303]=132;
piso[304]=132;
piso[305]=132;
piso[306]=132;
piso[307]=132;
piso[308]=132;
piso[309]=132;
piso[310]=132;
piso[311]=132;
piso[312]=132;
piso[313]=132;
piso[314]=132;
piso[315]=132;
piso[316]=132;
piso[317]=132;
piso[318]=132;
piso[319]=132;
piso[320]=132;
piso[321]=132;
piso[322]=132;
piso[323]=132;
piso[324]=132;
piso[325]=132;
piso[326]=132;
piso[327]=131;
piso[328]=131;
piso[329]=131;
piso[330]=131;
piso[331]=131;
piso[332]=131;
piso[333]=131;
piso[334]=131;
piso[335]=130;
piso[336]=130;
piso[337]=130;
piso[338]=130;
piso[339]=130;
piso[340]=130;
piso[341]=130;
piso[342]=130;
piso[343]=129;
piso[344]=129;
piso[345]=129;
piso[346]=129;
piso[347]=129;
piso[348]=129;
piso[349]=128;
piso[350]=128;
piso[351]=128;
piso[352]=128;
piso[353]=128;
piso[354]=128;
piso[355]=127;
piso[356]=127;
piso[357]=127;
piso[358]=127;
piso[359]=127;
piso[360]=127;
piso[361]=126;
piso[362]=126;
piso[363]=126;
piso[364]=126;
piso[365]=126;
piso[366]=126;
piso[367]=125;
piso[368]=125;
piso[369]=125;
piso[370]=125;
piso[371]=125;
piso[372]=125;
piso[373]=124;
piso[374]=124;
piso[375]=124;
piso[376]=124;
piso[377]=124;
piso[378]=124;
piso[379]=123;
piso[380]=123;
piso[381]=123;
piso[382]=123;
piso[383]=123;
piso[384]=123;
piso[385]=122;
piso[386]=122;
piso[387]=122;
piso[388]=122;
piso[389]=122;
piso[390]=122;
piso[391]=121;
piso[392]=121;
piso[393]=121;
piso[394]=121;
piso[395]=121;
piso[396]=121;
piso[397]=120;
piso[398]=120;
piso[399]=120;
piso[400]=120;
piso[401]=120;
piso[402]=120;
piso[403]=119;
piso[404]=119;
piso[405]=119;
piso[406]=119;
piso[407]=119;
piso[408]=119;
piso[409]=118;
piso[410]=118;
piso[411]=118;
piso[412]=118;
piso[413]=118;
piso[414]=118;
piso[415]=117;
piso[416]=117;
piso[417]=117;
piso[418]=117;
piso[419]=118;/////////
piso[420]=118;
piso[421]=118;
piso[422]=118;
piso[423]=119;
piso[424]=119;
piso[425]=119;
piso[426]=119;
piso[427]=119;
piso[428]=120;
piso[429]=120;////////
piso[430]=121;
piso[431]=121;
piso[432]=122;
piso[433]=122;
piso[434]=123;
piso[435]=123;
piso[436]=124;
piso[437]=124;
piso[438]=125;
piso[439]=125;////////
piso[440]=126;
piso[441]=126;
piso[442]=126;
piso[443]=126;
piso[444]=127;
piso[445]=127;
piso[446]=127;
piso[447]=127;
piso[448]=128;
piso[449]=128;////////
piso[450]=128;
piso[451]=128;
piso[452]=129;
piso[453]=129;
piso[454]=129;
piso[455]=129;
piso[456]=130;
piso[457]=130;
piso[458]=130;
piso[459]=130;////////
piso[460]=131;
piso[461]=131;
piso[462]=131;
piso[463]=131;
piso[464]=132;
piso[465]=132;
piso[466]=132;
piso[467]=132;
piso[468]=132;
piso[469]=133;////////
piso[470]=133;
piso[471]=133;
piso[472]=133;
piso[473]=133;
piso[474]=134;
piso[475]=134;
piso[476]=134;
piso[477]=134;
piso[478]=134;
piso[479]=136;///////
piso[480]=136;
piso[481]=136;
piso[482]=136;
piso[483]=136;
piso[484]=137;
piso[485]=137;
piso[486]=137;
piso[487]=137;
piso[488]=137;
piso[489]=138;//////
piso[490]=138;
piso[491]=138;
piso[492]=138;
piso[493]=138;
piso[494]=139;
piso[495]=139;
piso[496]=139;
piso[497]=139;
piso[498]=139;
piso[499]=140;///////
piso[500]=140;
piso[501]=140;
piso[502]=140;
piso[503]=140;
piso[504]=141;
piso[505]=141;
piso[506]=141;
piso[507]=141;
piso[508]=141;
piso[509]=142;///////

piso[510]=142;
piso[511]=142;
piso[512]=142;
piso[513]=142;
piso[514]=142;
piso[515]=143;
piso[516]=143;
piso[517]=143;
piso[518]=143;
piso[519]=143;


}
/**
    x coor x de suelo
    xMountan coor x de montañas
    xHorizon coor x de el horizonte
*/
void escenario1(SCENE move){
    SDL_Rect cielo;
        cielo.x=10+move.xHorizon; cielo.y=408;
        cielo.w=502+move.xHorizon; cielo.h=112;
    SDL_Rect tierraLejana;
        tierraLejana.x=10+move.xMountain; tierraLejana.y=560;
        tierraLejana.w=502+move.xMountain; tierraLejana.h=168;
        SDL_Rect coorTieLej;
            coorTieLej.x=0;
            coorTieLej.y=57;

    SDL_Rect tierra;
        tierra.x=10+move.x; tierra.y=10;
        tierra.w=502+move.x; tierra.h=250;

    SDL_BlitSurface(move.scene,&cielo,move.screen,NULL);
    SDL_BlitSurface(move.scene,&tierraLejana,move.screen,&coorTieLej);
    SDL_BlitSurface(move.scene,&tierra,move.screen,NULL);
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
                            ToggleFullscreen(window,screen);//Necesita trabajo
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
