/**
 *02 de agosto de 2017
 *Funciones de manejo de sprites
*/

#include "animation.h"

/**Funciones Arrays*/
void clarkStandSetRect(SDL_Rect torzo[4],SDL_Rect pierna[1]){
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

void clarkLowerBodyRunSetRect(SDL_Rect lowerBody[6]){
    lowerBody[0].x=13;  lowerBody[0].y=434;
    lowerBody[0].w=34;  lowerBody[0].h=34;
    lowerBody[1].x=57;  lowerBody[1].y=434;
    lowerBody[1].w=34;  lowerBody[1].h=34;         
    lowerBody[2].x=101; lowerBody[2].y=434;
    lowerBody[2].w=34;  lowerBody[2].h=34;
    lowerBody[3].x=133; lowerBody[3].y=434;
    lowerBody[3].w=34;  lowerBody[3].h=34;
    lowerBody[4].x=167; lowerBody[4].y=434;
    lowerBody[4].w=34;  lowerBody[4].h=34;
    lowerBody[5].x=201; lowerBody[5].y=434;
    lowerBody[5].w=34;  lowerBody[5].h=34;//----------------------------
}

void clarkUpperBodyShootSetRect(SDL_Rect upperBody[9]){
    upperBody[0].x=19;   upperBody[0].y=50;//Disparando adelante------------
    upperBody[0].w=35;   upperBody[0].h=35;

    upperBody[1].x=85;   upperBody[1].y=50;
    upperBody[1].w=35;   upperBody[1].h=35;

    upperBody[2].x=153;  upperBody[2].y=50;
    upperBody[2].w=35;   upperBody[2].h=35;

    upperBody[3].x=206;  upperBody[3].y=50;
    upperBody[3].w=35;   upperBody[3].h=35;

    upperBody[4].x=206;  upperBody[4].y=50;
    upperBody[4].w=35;   upperBody[4].h=35;

    upperBody[5].x=303;  upperBody[5].y=50;
    upperBody[5].w=35;   upperBody[5].h=35;

    upperBody[6].x=352;  upperBody[6].y=50;
    upperBody[6].w=35;   upperBody[6].h=35;

    upperBody[7].x=401;  upperBody[7].y=48;
    upperBody[7].w=35;   upperBody[7].h=35;

    upperBody[8].x=449;  upperBody[8].y=49;
    upperBody[8].w=35;   upperBody[8].h=35;

    upperBody[9].x=498;  upperBody[9].y=50;
    upperBody[9].w=35;   upperBody[9].h=35;//------
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

void clarkPier(GRAPH g,int x,int y,SDL_Rect pierna[]){
    SDL_Rect pierCoor;

    //pierna.x=580; pierna.y=20;
    //pierna.w=30; pierna.h=30;//-----------------------------

    pierCoor.x=0+x; pierCoor.y=41+y;//Piernas

    SDL_BlitSurface(g.player,&pierna[0],g.screen,&pierCoor);//Clark torzo
    SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
}

void clarkPiernasRunArr(SDL_Rect torzo[4],SDL_Rect pierna[6]){
    //Corriendo---------------------------------------------------
    pierna[0].x=  13; pierna[0].y=   434;
    pierna[0].w=  34; pierna[0].h=    34;

    pierna[1].x=  57; pierna[1].y=   434;
    pierna[1].w=  34; pierna[1].h=    34;

    pierna[2].x= 101; pierna[2].y=  434;
    pierna[2].w=  34;  pierna[2].h=  34;

    pierna[3].x= 133; pierna[3].y=  434;
    pierna[3].w=  34;  pierna[3].h=  34;

    pierna[4].x= 167; pierna[4].y=  434;
    pierna[4].w=  34;  pierna[4].h=  34;

    pierna[5].x= 201; pierna[5].y=  434;
    pierna[5].w=  34;  pierna[5].h=  34;//----------------------------
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


/**Funciones movimiento
 *================================================================
 */
void clarkStand(GRAPH g,int *iT,int *iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
        SDL_Rect torCoor,pierCoor;

            /*torzo[0][2].x=10; torzo[0][2].y=85;//Apuntando arriba---------------
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
//Disparando
void clarkShoot(GRAPH g,int *iT,int x,int y,SDL_Rect torzo[]){
        SDL_Rect torCoor;

        torCoor.x=2+x; torCoor.y=20+y;//Torzo

        if(g.player) {//Manejo de error
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
