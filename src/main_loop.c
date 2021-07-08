#include "main_loop.h"




void mainLoop(Graphic_elements graphic_elements){
    struct SdlConfig Config;
    SDL_Surface* sceneSurface;
    SDL_Surface* playerSurface;
    
    
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

    Events events = {
        .key_left     =     false,
        .key_right    =     false,
        .key_down     =     false,
        .key_up       =     false,
        .key_shoot    =     false,
        .key_jump     =     false,
        .fullscreen   =     false
    };
    
    int hight[3824];
    int hightIndex = 50;
    int jumpHight[52];
    int jumpIndex = 0;


    
    readMeasurements(jumpHight , "../assets/measurements/jump.txt" , 50);
    readMeasurements(hight     , "../assets/measurements/floor.txt", 535);


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

    setConfiguration(&Config);

    while (1) {

        frameStart = SDL_GetTicks();

        handleEvents(graphic_elements.window, &events, &Config.i, hight[hightIndex]);

        /**Movement */
        if(events.key_right) {
            Config.rects.playerUpperBodyPosition.x+=1;
            Config.rects.playerLowerBodyPosition.x+=1;
            Config.rects.playerLowerBodyPositionBackward.x+=1;
        }

        else if(events.key_left) {
            Config.rects.playerUpperBodyPosition.x-=1;
            Config.rects.playerLowerBodyPosition.x-=1;
            Config.rects.playerLowerBodyPositionBackward.x-=1;
        }

        

        SDL_RenderClear(graphic_elements.sceneRenderer);
        SDL_RenderCopy(graphic_elements.sceneRenderer, graphic_elements.sceneSkyTexture, &Config.rects.skyRect, NULL);
        SDL_RenderCopy(graphic_elements.sceneRenderer, graphic_elements.sceneHorizonTexture, &Config.rects.horizonRect, NULL);
        SDL_RenderCopy(graphic_elements.sceneRenderer, graphic_elements.sceneFloorTexture, &Config.rects.floorRect, NULL);
        //There are some troubles with the trace
        //SDL_RenderCopy(graphic_elements.sceneRenderer, graphic_elements.sceneFloorTexture, &rects.traceRect, NULL);

        if(events.key_right) {
            direction = forward;
            Config.rects.lowerBodyBaseRect = Config.rects.lowerBodyRunRect[Config.i.lowerBodyRunIndex];
            if(run) {
                Config.i.lowerBodyRunIndex++;
            }
            hightIndex++;
            Config.rects.traceRect.w++;
        }
        else if(events.key_left) {
            direction = backward;
            Config.rects.lowerBodyBaseRect = Config.rects.lowerBodyRunRect[Config.i.lowerBodyRunIndex];
            if(run) {
                Config.i.lowerBodyRunIndex++;
            }
            hightIndex--;
        }

        else {
            Config.rects.lowerBodyBaseRect = Config.rects.lowerBodyRect[Config.i.lowerBodyStandIndex];
            if(!events.key_shoot)
                Config.rects.upperBodyBaseRect = Config.rects.upperBodyRect[Config.i.upperBodyStandIndex];
            run = false;
        }

        if (events.key_shoot){
            Config.rects.upperBodyBaseRect = Config.rects.upperBodyShootRect[Config.i.upperBodyShootIndex];
            if(shoot){
                Config.i.upperBodyShootIndex++;
            }

            if( Config.i.upperBodyShootIndex >= 9){
                Config.i.upperBodyShootIndex = 0;
                events.key_shoot = false;
            }
        }

        if(events.key_jump){
            
            if( jumpIndex >= 50 ){
                jumpIndex = 0;
                events.key_jump = false;
            }

            Config.rects.playerUpperBodyPosition.y -= jumpHight[jumpIndex];
            Config.rects.playerLowerBodyPosition.y -= jumpHight[jumpIndex];
            Config.rects.playerLowerBodyPositionBackward.y -= jumpHight[jumpIndex];

            //if(jump)
            jumpIndex++;
            //printf("h: %d\n", Config.rects.playerLowerBodyPositionBackward.y);
            
        }

        if(direction) {
            SDL_RenderCopy(graphic_elements.sceneRenderer  ,  graphic_elements.playerTexture
                         , &Config.rects.lowerBodyBaseRect              , &Config.rects.playerLowerBodyPosition);

            SDL_RenderCopy(graphic_elements.sceneRenderer  ,  graphic_elements.playerTexture
                         , &Config.rects.upperBodyBaseRect              , &Config.rects.playerUpperBodyPosition);

        }

        else if(!direction) {
            SDL_RenderCopyEx(graphic_elements.sceneRenderer, graphic_elements.playerTexture
                           , &Config.rects.lowerBodyBaseRect            , &Config.rects.playerLowerBodyPositionBackward
                           , 0.0                           , NULL
                           , graphic_elements.rendererFlip        );

            SDL_RenderCopyEx(graphic_elements.sceneRenderer, graphic_elements.playerTexture
                           , &Config.rects.upperBodyBaseRect            , &Config.rects.playerUpperBodyPosition
                           , 0.0                           , NULL
                           , graphic_elements.rendererFlip        );

        }

        if(breath){
            Config.i.upperBodyStandIndex++;
        }

        if( Config.i.upperBodyStandIndex >= 4){
            Config.i.upperBodyStandIndex = 0;
        }

        if(Config.i.lowerBodyRunIndex >= 6){
            Config.i.lowerBodyRunIndex = 0;
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
        

        if(events.fullscreen) {
            printf("fullscreen\n");
            Config.rects.playerUpperBodyPosition.y         =      hight[hightIndex] + Config.rects.fullScreenHightCompensation;
            Config.rects.playerLowerBodyPosition.y         = 21 + hight[hightIndex] + Config.rects.fullScreenHightCompensation;
            Config.rects.playerLowerBodyPositionBackward.y = 21 + hight[hightIndex] + Config.rects.fullScreenHightCompensation;
        } else {
            Config.rects.playerUpperBodyPosition.y         =      hight[hightIndex];
            Config.rects.playerLowerBodyPosition.y         = 21 + hight[hightIndex];
            Config.rects.playerLowerBodyPositionBackward.y = 21 + hight[hightIndex];
        }

        SDL_RenderPresent(graphic_elements.sceneRenderer);

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

    }

}
