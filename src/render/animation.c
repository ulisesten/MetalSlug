#include "animation.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void clarkStandArr(SDL_Rect torso[4],SDL_Rect pierna[1]){
    torso[0].x=10; torso[0].y=5;//Parado--------------------------
    torso[0].w=35; torso[0].h=35;

    torso[1].x=43; torso[1].y=5;
    torso[1].w=35; torso[1].h=35;

    torso[2].x=76; torso[2].y=5;
    torso[2].w=35; torso[2].h=35;

    torso[3].x=109; torso[3].y=5;
    torso[3].w=35; torso[3].h=35;

    pierna[0].x=145; pierna[0].y=20;
    pierna[0].w=35; pierna[0].h=34;//-----------------------------
}

void clarkStandBackArr(SDL_Rect torso[4],SDL_Rect pierna[1]){
    torso[0].x=710; torso[0].y=5;//Parado--------------------------
    torso[0].w=30; torso[0].h=30;

    torso[1].x=677; torso[1].y=5;
    torso[1].w=30; torso[1].h=30;

    torso[2].x=644; torso[2].y=5;
    torso[2].w=30; torso[2].h=30;

    torso[3].x=611; torso[3].y=5;
    torso[3].w=30; torso[3].h=30;

    pierna[0].x=580; pierna[0].y=20;
    pierna[0].w=30; pierna[0].h=30;//-----------------------------
}

void clarkRunArr(SDL_Rect torso[4],SDL_Rect pierna[6]){
    torso[0].x=10; torso[0].y=5;//Parado--------------------------
    torso[0].w=35; torso[0].h=35;

    torso[1].x=43; torso[1].y=5;
    torso[1].w=35; torso[1].h=35;

    torso[2].x=76; torso[2].y=5;
    torso[2].w=35; torso[2].h=35;

    torso[3].x=109; torso[3].y=5;
    torso[3].w=35; torso[3].h=35;
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

/* Indexes clarkPier(GRAPH g,int x,int y,SDL_Rect pierna[]){
    SDL_Rect pierCoor;

    //pierna.x=580; pierna.y=20;
    //pierna.w=30; pierna.h=30;//-----------------------------

    pierCoor.x=0+x; pierCoor.y=41+y;//Piernas

    SDL_BlitSurface(g.player,&pierna[0],g.screen,&pierCoor);//Clark torzo
    SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    return (Indexes){1,1};
} */

/* void clarkPiernasRunArr(SDL_Rect torzo[4],SDL_Rect pierna[6]){
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
} */

void clarkRunBackArr(SDL_Rect torso[4],SDL_Rect pierna[6]){
    //Parado-------------------------------
    torso[0].x=710; torso[0].y=5;
    torso[0].w=30; torso[0].h=30;

    torso[1].x=677; torso[1].y=5;
    torso[1].w=30; torso[1].h=30;

    torso[2].x=644; torso[2].y=5;
    torso[2].w=30; torso[2].h=30;

    torso[3].x=611; torso[3].y=5;
    torso[3].w=30; torso[3].h=30;
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

void clarkShootArr(SDL_Rect torso[9]){
    torso[0].x=19;   torso[0].y=50;//Disparando adelante------------
    torso[0].w=55;   torso[0].h=30;

    torso[1].x=85;   torso[1].y=50;
    torso[1].w=55;   torso[1].h=30;

    torso[2].x=153;  torso[2].y=50;
    torso[2].w=57;   torso[2].h=30;

    torso[3].x=206;  torso[3].y=50;
    torso[3].w=37;   torso[3].h=30;

    torso[4].x=206;  torso[4].y=50;
    torso[4].w=50;   torso[4].h=30;

    torso[5].x=303;  torso[5].y=50;
    torso[5].w=45;   torso[5].h=30;

    torso[6].x=352;  torso[6].y=50;
    torso[6].w=45;   torso[6].h=30;

    torso[7].x=401;  torso[7].y=48;
    torso[7].w=40;   torso[7].h=30;

    torso[8].x=449;  torso[8].y=49;
    torso[8].w=35;   torso[8].h=30;

    torso[9].x=498;  torso[9].y=50;
    torso[9].w=35;   torso[9].h=30;
}

void clarkUpTorsoArr(SDL_Rect torso[4]) {
    torso[0].x = 10;  torso[0].y = 85;  torso[0].w = 35;  torso[0].h = 35;
    torso[1].x = 43;  torso[1].y = 85;  torso[1].w = 33;  torso[1].h = 35;
    torso[2].x = 76;  torso[2].y = 85;  torso[2].w = 35;  torso[2].h = 35;
    torso[3].x = 109; torso[3].y = 85;  torso[3].w = 35;  torso[3].h = 35;
}

void initAnimations(AnimationArrays* ani_arrays) {
    initClarkAnimations(ani_arrays);
    // Aquí puedes agregar más inicializaciones de personajes
}

void initClarkAnimations(AnimationArrays* ani_arrays) {
    clarkStandArr(      ani_arrays->StandTorso,      ani_arrays->StandLegs);
    clarkStandBackArr(  ani_arrays->StandBackTorso,  ani_arrays->StandBackLegs);
    clarkRunArr(        ani_arrays->RunTorso,        ani_arrays->RunLegs);
    clarkRunBackArr(    ani_arrays->RunBackTorso,    ani_arrays->RunBackLegs);
    clarkShootArr(      ani_arrays->ShootTorso);
}



/**Funciones movimiento
 *================================================================
 */
Indexes clarkStand(GRAPH g,int *iT,int *iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
        SDL_Rect torCoor,pierCoor;

            //Corregir medidas partir de aqui
            //Necesita variable tAux para compensar altura
            /*torzo[0][3].x=12; torzo[0][3].y=145;//Disparando arriba-------------
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
        } else {
            printf("IMG_Load: %s\n", IMG_GetError());
        }

        return (Indexes){4,1};
}



//Disparando
Indexes clarkShoot(GRAPH g,int *iT,int x,int y,SDL_Rect torzo[]){
        SDL_Rect torCoor;

        torCoor.x=2+x; torCoor.y=20+y;//Torzo

        if(g.player) {//Manejo de error
            SDL_BlitSurface(g.player,&torzo[*iT],g.screen,&torCoor);//Clark torzo
            SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
        } else {
            printf("IMG_Load: %s\n", IMG_GetError());
        }

        return (Indexes){9,1};
}


Indexes clarkStandBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
    SDL_Rect torCoor,pierCoor;

    torCoor.x=2+x; torCoor.y=20+y;//Torzo
    pierCoor.x=9+x; pierCoor.y=41+y;//Piernas

    if(g.player) {//Manejo de error
        SDL_BlitSurface(g.playerBack,&pierna[0],g.screen,&pierCoor);//Clark piernas
        SDL_BlitSurface(g.playerBack,&torzo[iT],g.screen,&torCoor);//Clark torzo
        SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    } else {
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    return (Indexes){4,1};
}

Indexes clarkRun(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
    SDL_Rect torCoor,pierCoor;

    torCoor.x=2+x; torCoor.y=20+y;//Torzo
    pierCoor.x=0+x; pierCoor.y=41+y;//Piernas

    if(g.player) {//Manejo de error
        //printf("%d , %d",iT,iP);
        SDL_BlitSurface(g.player,&pierna[iP],g.screen,&pierCoor);//Clark piernas
        SDL_BlitSurface(g.player,&torzo[0],g.screen,&torCoor);//Clark torzo
        SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    } else {
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    return (Indexes){4,6};
}

Indexes clarkRunBack(GRAPH g,int iT,int iP,int x,int y,SDL_Rect torzo[],SDL_Rect pierna[]){
    SDL_Rect torCoor,pierCoor;

    torCoor.x=0+x; torCoor.y=20+y;//Torzo coor
    pierCoor.x=7+x; pierCoor.y=41+y;//Piernas coor

    if(g.player) {//Manejo de error
        SDL_BlitSurface(g.playerBack,&pierna[iP],g.screen,&pierCoor);//Clark piernas
        SDL_BlitSurface(g.playerBack,&torzo[iT],g.screen,&torCoor);//Clark torzo
        SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    } else {
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    return (Indexes){4,6};
}



Indexes clarkStandV2(GRAPH g, PlayerState pla_state, AnimationArrays ani_arrays){
    if(!g.player) {
        printf("IMG_Load: %s\n", IMG_GetError());
        return (Indexes){0,0};
    }

    SDL_Rect torso_coors, leg_coors;

    const int x = pla_state.x;
    const int y = pla_state.y;
    const int i = pla_state.iTorso;

    torso_coors.x= x + 2;
    torso_coors.y= y + 20;

    leg_coors.x= 0+x;
    leg_coors.y=41+y;//Piernas

    SDL_BlitSurface(g.player,&ani_arrays.StandLegs[0],g.screen, &leg_coors);//Clark piernas
    SDL_BlitSurface(g.player,&ani_arrays.ShootTorso[i],g.screen,&torso_coors);//Clark torzo
    SDL_UpdateWindowSurface(g.window);//Refrescando pantalla    

    return (Indexes){4,1};
}

Indexes clarkStandBackV2(GRAPH g, PlayerState pla_state, AnimationArrays ani_arrays){
    if(!g.player) {
        printf("IMG_Load: %s\n", IMG_GetError());
        return (Indexes){0,0};
    }

    SDL_Rect torso_coors, leg_coors;

    const int x = pla_state.x;
    const int y = pla_state.y;
    const int i = pla_state.iTorso;

    torso_coors.x=  2+x;
    torso_coors.y= 20+y;//Torzo
    leg_coors.x =   9+x;
    leg_coors.y=   41+y;//Piernas

    SDL_BlitSurface(g.playerBack,&ani_arrays.StandBackLegs[0],g.screen,&leg_coors);//Clark piernas
    SDL_BlitSurface(g.playerBack,&ani_arrays.StandBackTorso[i],g.screen,&torso_coors);//Clark torzo
    SDL_UpdateWindowSurface(g.window);//Refrescando pantalla
    
    return (Indexes){4,1};
}

Indexes clarkRunV2(GRAPH g, PlayerState* pla_state, AnimationArrays* ani_arrays){
    if(!g.player) {
        printf("IMG_Load: %s\n", IMG_GetError());
        return (Indexes){0,0};
    }

    SDL_Rect torso_coors, leg_coors;

    const int x = pla_state->x;
    const int y = pla_state->y;
    const int i = pla_state->iPierna;
    const int j = pla_state->iTorso;

    torso_coors.x=2+x;
    torso_coors.y=20+y;//Torzo

    leg_coors.x=0+x;
    leg_coors.y=41+y;//Piernas

    
    SDL_BlitSurface(g.player,&ani_arrays->RunLegs[i],g.screen,&leg_coors);//Clark piernas
    SDL_BlitSurface(g.player,&ani_arrays->RunTorso[j],g.screen,&torso_coors);//Clark torzo
    SDL_UpdateWindowSurface(g.window);//Refrescando pantalla

    return (Indexes){4,6};
}

Indexes clarkRunBackV2(GRAPH g, PlayerState* pla_state, AnimationArrays* ani_arrays){
    if(!g.player) {
        printf("IMG_Load: %s\n", IMG_GetError());
        return (Indexes){0,0};
    }

    SDL_Rect torso_coors, leg_coors;

    const int x = pla_state->x;
    const int y = pla_state->y;
    const int i = pla_state->iTorso;
    const int j = pla_state->iPierna;

    torso_coors.x=0+x;
    torso_coors.y=20+y;//Torzo coor

    leg_coors.x=7+x;
    leg_coors.y=41+y;//Piernas coor

    
    SDL_BlitSurface(g.playerBack,&ani_arrays->RunBackLegs[j],g.screen,&leg_coors);//Clark piernas
    SDL_BlitSurface(g.playerBack,&ani_arrays->RunBackTorso[i],g.screen,&torso_coors);//Clark torzo
    SDL_UpdateWindowSurface(g.window);//Refrescando pantalla

    return (Indexes){4,6};
}