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
#include "movement.h"
#include "selection_menu.h"

typedef struct {
    
	SDL_Window*    window             =  NULL;
	SDL_Surface*   screen             =  NULL;
	SDL_Renderer* sceneRenderer       =  NULL;
	SDL_Texture* sceneFloorTexture    =  NULL;
    SDL_Texture* sceneHorizonTexture  =  NULL;
    SDL_Texture* sceneSkyTexture      =  NULL;
	SDL_Texture* playerTexture        =  NULL;
    SDL_RendererFlip rendererFlip = SDL_FLIP_HORIZONTAL;

} Graphic_elements;


void mainLoop(         Graphic_elements graphic_elements );
void destroySurfaces(  Graphic_elements graphic_elements );
void player();
void setRects(         Rects*           rects );
void stage_1_scene(    SCENE            scene );


int main ( int argc, char** argv ){

	Graphic_elements m_graphic_elements;
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

            if(m_graphic_elements.screen)
            
                mainLoop(m_graphic_elements);

            else

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


void mainLoop(Graphic_elements graphic_elements){
    SDL_Surface* sceneSurface;
    SDL_Surface* playerSurface;

    SDL_Rect upperBodyBaseRect;
    SDL_Rect upperBodyRect[4];
    SDL_Rect upperBodyShootRect[9];
    SDL_Rect lowerBodyBaseRect;
    SDL_Rect lowerBodyRect[4];
    SDL_Rect lowerBodyRunRect[6];

    int upperBodyStandIndex = 0;
    int upperBodyShootIndex = 0;
    int lowerBodyStandIndex = 0;
    int lowerBodyRunIndex   = 0;
    
    unsigned int pastBreath  = 0, currentBreath = 0;
    unsigned int pastRun     = 0, currentRun    = 0;
    unsigned int pastShoot   = 0, currentShoot  = 0;
    unsigned int pastJump    = 0, currentJump   = 0;

    bool breath      =  false;
    bool run         =  false;
    bool shoot       =  false;
    bool isShooting  =  false;
    bool jump        =  false;
    bool forward     =  true;
    bool backward    =  false;
    bool direction   =  forward;
	
    Rects rects;
    Events events;
    Indices i;
    
    int hight[3824];
    int hightIndex = 0;
    int jumpHight[52];
    int jumpIndex = 0;


    setRects(&rects);
    readMeasurements(hight, "../assets/measurements/floor.txt", 535);
    readMeasurements(jumpHight, "../assets/measurements/jump.txt", 52);
    int i2;
    for(i2 = 0; i2 < 52; i2++){
        printf("jump: %d\n", jumpHight[i2]);
    }

    clarkStandSetRect(upperBodyRect, lowerBodyRect);
    clarkLowerBodyRunSetRect(lowerBodyRunRect);
    clarkUpperBodyShootSetRect(upperBodyShootRect);

	/**Loading surfaces*/
	sceneSurface  = IMG_Load("../assets/mision1.png");
    playerSurface  = IMG_Load("../assets/clark.png");

    if (!sceneSurface) {
        printf("error in sceneSurface\n");
    }
    
    if (!playerSurface) {
        printf("error in playerSurface\n");
    }

    /**Creating renderer */
	graphic_elements.sceneRenderer = SDL_CreateRenderer(graphic_elements.window, -1, SDL_RENDERER_ACCELERATED);
	graphic_elements.sceneFloorTexture  = SDL_CreateTextureFromSurface(graphic_elements.sceneRenderer, sceneSurface);
    graphic_elements.sceneHorizonTexture  = SDL_CreateTextureFromSurface(graphic_elements.sceneRenderer, sceneSurface);
    graphic_elements.sceneSkyTexture  = SDL_CreateTextureFromSurface(graphic_elements.sceneRenderer, sceneSurface);
	graphic_elements.playerTexture = SDL_CreateTextureFromSurface(graphic_elements.sceneRenderer, playerSurface);
    
    /**Destroying surfaces */
    SDL_FreeSurface(sceneSurface);
	SDL_FreeSurface(playerSurface);

    int fps = 60;
    int frameDelay = 1000/fps;

    Uint32 frameStart;
    int frameTime;

    while (1) {

        frameStart = SDL_GetTicks();

        handleEvents(&rects,graphic_elements.window, &events, &i, hight[hightIndex]);

        SDL_RenderClear(graphic_elements.sceneRenderer);
        SDL_RenderCopy(graphic_elements.sceneRenderer, graphic_elements.sceneSkyTexture, &rects.skyRect, NULL);
        SDL_RenderCopy(graphic_elements.sceneRenderer, graphic_elements.sceneHorizonTexture, &rects.horizonRect, NULL);
        SDL_RenderCopy(graphic_elements.sceneRenderer, graphic_elements.sceneFloorTexture, &rects.floorRect, NULL);
        //There are some troubles with the trace
        //SDL_RenderCopy(graphic_elements.sceneRenderer, graphic_elements.sceneFloorTexture, &rects.traceRect, NULL);

        if(events.key_right) {
            direction = forward;
            lowerBodyBaseRect = lowerBodyRunRect[lowerBodyRunIndex];
            if(run) {
                lowerBodyRunIndex++;
            }
            hightIndex++;
            rects.traceRect.w++;
        }
        else if(events.key_left) {
            direction = backward;
            lowerBodyBaseRect = lowerBodyRunRect[lowerBodyRunIndex];
            if(run) {
                lowerBodyRunIndex++;
            }
            hightIndex--;
        }

        else {
            lowerBodyBaseRect = lowerBodyRect[lowerBodyStandIndex];
            if(!events.key_shoot)
                upperBodyBaseRect = upperBodyRect[upperBodyStandIndex];
            run = false;
        }

        if (events.key_shoot){
            upperBodyBaseRect = upperBodyShootRect[i.upperBodyShootIndex];
            if(shoot){
                i.upperBodyShootIndex++;
            }

            if( i.upperBodyShootIndex >= 9){
                i.upperBodyShootIndex = 0;
                events.key_shoot = false;
            }
        }

        if(events.key_jump){

            rects.playerUpperBodyPosition.y -= jumpHight[jumpIndex];
            rects.playerLowerBodyPosition.y -= jumpHight[jumpIndex];
            rects.playerLowerBodyPositionBackward.y -= jumpHight[jumpIndex];
            if(jump){
                //printf("h: %d, %d\n", jumpIndex, jumpHight[jumpIndex]);
                jumpIndex++;
            }

            if( jumpIndex == 52 ){
                jumpIndex = 0;
                events.key_jump = false;
            }
            
        }

        if(direction) {
            SDL_RenderCopy(graphic_elements.sceneRenderer  ,  graphic_elements.playerTexture
                         , &lowerBodyBaseRect              , &rects.playerLowerBodyPosition);

            SDL_RenderCopy(graphic_elements.sceneRenderer  ,  graphic_elements.playerTexture
                         , &upperBodyBaseRect              , &rects.playerUpperBodyPosition);

        }

        else if(!direction) {
            SDL_RenderCopyEx(graphic_elements.sceneRenderer, graphic_elements.playerTexture
                           , &lowerBodyBaseRect            , &rects.playerLowerBodyPositionBackward
                           , 0.0                           , NULL
                           , graphic_elements.rendererFlip        );

            SDL_RenderCopyEx(graphic_elements.sceneRenderer, graphic_elements.playerTexture
                           , &upperBodyBaseRect            , &rects.playerUpperBodyPosition
                           , 0.0                           , NULL
                           , graphic_elements.rendererFlip        );

        }

        if(breath){
            upperBodyStandIndex++;
        }

        if( upperBodyStandIndex >= 4){
            upperBodyStandIndex = 0;
        }

        if(lowerBodyRunIndex >= 6){
            lowerBodyRunIndex = 0;
        }

        breath  = false;
        run     = false;
        shoot   = false;
        jump    = false;

        currentBreath     =    SDL_GetTicks();
        currentRun        =    SDL_GetTicks();
        currentShoot      =    SDL_GetTicks();
        currentJump       =    SDL_GetTicks();

        if(currentBreath  >    pastBreath + 200){
            breath        =    true;
            pastBreath    =    currentBreath;
        }

        if(currentRun     >    pastRun + 120){
            run           =    true;
            pastRun       =    currentRun;
        }

        if(currentShoot   >    pastShoot + 30){
            shoot         =    true;
            pastShoot     =    currentShoot;
        }

        if( currentJump   >    pastJump + 10){
            jump          =    true;
            pastJump      =    currentJump;
        }

        SDL_RenderPresent(graphic_elements.sceneRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

    }

}

void setRects( Rects* rects ){
    rects->fullScreenHightCompensation = 40;

    rects->floorRect.x = 0;
	rects->floorRect.y = 0;
	rects->floorRect.w = 502;
	rects->floorRect.h = 248;

    rects->traceRect.x = 0;
    rects->traceRect.y = 287;
    rects->traceRect.w = 502;
    rects->traceRect.h = 72;

    rects->horizonRect.x = 10;
    rects->horizonRect.y = 560;
    rects->horizonRect.w = 502;
    rects->horizonRect.h = 248;

    rects->skyRect.x = 10;
    rects->skyRect.y = 408;
    rects->skyRect.w = 502;
    rects->skyRect.h = 248;

    rects->playerSpriteFrame.x = 10;
	rects->playerSpriteFrame.y = 5;
	rects->playerSpriteFrame.w = 35;
	rects->playerSpriteFrame.h = 35;

    rects->playerUpperBodyPosition.x = -28;
    rects->playerUpperBodyPosition.y = 0; //old 50
    rects->playerUpperBodyPosition.w = 35;
    rects->playerUpperBodyPosition.h = 35;

    rects->playerLowerBodyPosition.x = -30;
    rects->playerLowerBodyPosition.y = 21; //old 71
    rects->playerLowerBodyPosition.w = 35;
    rects->playerLowerBodyPosition.h = 35;

    rects->playerLowerBodyPositionBackward.x = -26;
    rects->playerLowerBodyPositionBackward.y = 21; //old 71
    rects->playerLowerBodyPositionBackward.w = 35;
    rects->playerLowerBodyPositionBackward.h = 35;
}


void destroySurfaces(Graphic_elements graphic_elements){
	
	/**Destroy Scene stuff*/
	SDL_DestroyRenderer(graphic_elements.sceneRenderer);
	SDL_DestroyTexture(graphic_elements.sceneFloorTexture);
	
	/**Destroy Player stuff*/
	SDL_DestroyTexture(graphic_elements.playerTexture);
	
	SDL_DestroyWindow(graphic_elements.window);

}
	


void player(){
	
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