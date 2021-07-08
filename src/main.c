#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_joystick.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_image.h>
#include "floor.h"
//#include "animation.h"
//#include "movement.h"
#include "character_selection.h"
#include "main_loop.h"


void destroySurfaces( Graphic_elements graphic_elements );
void stage_1_scene(           SCENE            scene );


int main ( int argc, char** argv ){

	Graphic_elements m_graphic_elements = {
        .rendererFlip = SDL_FLIP_HORIZONTAL
    };

	SDL_Window*      window       =  NULL;
	SDL_Surface*     screen       =  NULL;
    
    if(IMG_Init(IMG_INIT_PNG) > -1)
        printf("IMG_Init success\n");
    else
        printf("IMG_Init error\n");

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)>-1){//Iniciando soporte de video

        //Creating window
        m_graphic_elements.window = SDL_CreateWindow( "Metal Slug",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED
                                                      ,502,238,SDL_WINDOW_SHOWN);

        if(m_graphic_elements.window){
            
            //Creating screen
            m_graphic_elements.screen = SDL_GetWindowSurface(m_graphic_elements.window);

            if(m_graphic_elements.screen){

                //character_selection(screen, window);
                mainLoop(m_graphic_elements);

            } else

                printf("Creating screen ERROR!\n");

        } else {

            printf("Error SDL_CreateWindow %s",SDL_GetError());

        }

    } else {

        printf("Error SDL_Init %s",SDL_GetError());

    }

    destroySurfaces(m_graphic_elements);//Cerrando ventana
    IMG_Quit();
    SDL_Quit();//Cerrando SDL

    return 0;

}


void destroySurfaces(Graphic_elements graphic_elements){
	/**Destroy Scene stuff*/
	SDL_DestroyRenderer(graphic_elements.sceneRenderer);
	SDL_DestroyTexture(graphic_elements.sceneFloorTexture);
	SDL_DestroyTexture(graphic_elements.playerTexture);
	SDL_DestroyWindow(graphic_elements.window);
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
void stage_1_scene(SCENE move) {

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

    SDL_BlitSurface(move.scene, &cielo,        move.screen,  NULL);
    SDL_BlitSurface(move.scene, &tierraLejana, move.screen, &coorTieLej);
    SDL_BlitSurface(move.scene, &tierra,       move.screen,  NULL);

}