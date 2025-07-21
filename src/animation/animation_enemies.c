#include "animation_enemies.h"
#include "animation.h"


void initEnemyAnimations(AnimationEnemyArrays* ene_arrays) {
    initSoldierAnimations(ene_arrays);
}

void initSoldierAnimations(AnimationEnemyArrays* ene_arrays) {
    soldierKnifeArray(ene_arrays->enemyKnifeBody);
    soldierScaredArray(ene_arrays->enemyScaredBody);
    soldierCasualArray(ene_arrays->enemyCasualBody);
}

void soldierKnifeArray(SDL_Rect body[18]) {
    body[0].x = 5;   body[0].y = 1043;  body[0].w = 25;  body[0].h = 37;
    body[1].x = 35;  body[1].y = 1043;  body[1].w = 25;  body[1].h = 37;
    body[2].x = 62;  body[2].y = 1043;  body[2].w = 25;  body[2].h = 37;
    body[3].x = 88;  body[3].y = 1043;  body[3].w = 25;  body[3].h = 37;
    body[4].x = 115; body[4].y = 1043;  body[4].w = 25;  body[4].h = 37;
    body[5].x = 144; body[5].y = 1043;  body[5].w = 25;  body[5].h = 37;
    body[6].x = 176; body[6].y = 1043;  body[6].w = 25;  body[6].h = 37;
    body[7].x = 210; body[7].y = 1043;  body[7].w = 25;  body[7].h = 37;
    body[8].x = 244; body[8].y = 1043;  body[8].w = 35;  body[8].h = 37;
    body[9].x = 279; body[9].y = 1043;  body[9].w = 43;  body[9].h = 37;
    body[10].x = 327; body[10].y = 1043;  body[10].w = 45;  body[10].h = 37;
    body[11].x = 381; body[11].y = 1043;  body[11].w = 45;  body[11].h = 37;
    body[12].x = 327; body[12].y = 1043;  body[12].w = 45;  body[12].h = 37;
    body[13].x = 279; body[13].y = 1043;  body[13].w = 43;  body[13].h = 37;
    body[14].x = 244; body[14].y = 1043;  body[14].w = 35;  body[14].h = 37;
    body[15].x = 210; body[15].y = 1043;  body[15].w = 25;  body[15].h = 37;
    body[16].x = 176; body[16].y = 1043;  body[16].w = 25;  body[16].h = 37;
    body[17].x = 144; body[17].y = 1043;  body[17].w = 25;  body[17].h = 37;
}

EnemyIndexes soldierKnifeAttack(GRAPH g, EnemyState ene_state) {
    SDL_Rect body_coors;

    const int x = ene_state.x;
    const int y = ene_state.y;
    const int i = ene_state.iBody;

    body_coors.x = x;
    body_coors.y = y;

    SDL_BlitSurface(g.soldier, &ene_state.ani_arrays->enemyKnifeBody[i], g.screen, &body_coors);

    return (EnemyIndexes){18};
}

void soldierScaredArray(SDL_Rect body[11]) {
    body[0].x =    5;   body[0].y =  242;  body[0].w =  33;  body[0].h  = 47;
    body[1].x =   38;   body[1].y =  242;  body[1].w =  41;  body[1].h  = 47;
    body[2].x =   84;   body[2].y =  242;  body[2].w =  41;  body[2].h  = 47;
    body[3].x =  132;   body[3].y =  242;  body[3].w =  41;  body[3].h  = 47;
    body[4].x =  178;   body[4].y =  242;  body[4].w =  41;  body[4].h  = 47;
    body[5].x =  226;   body[5].y =  242;  body[5].w =  41;  body[5].h  = 47;
    body[6].x =  272;   body[6].y =  242;  body[6].w =  41;  body[6].h  = 47;
    body[7].x =  320;   body[7].y =  242;  body[7].w =  41;  body[7].h  = 47;
    body[8].x =  366;   body[8].y =  242;  body[8].w =  41;  body[8].h  = 47;
    body[9].x =  414;   body[9].y =  242;  body[9].w =  41;  body[9].h  = 47;
    body[10].x = 460;   body[10].y = 242;  body[10].w = 41;  body[10].h = 47;
}

EnemyIndexes soldierScared(GRAPH g, EnemyState ene_state) {
    SDL_Rect body_coors;

    const int x = ene_state.x;
    const int y = ene_state.y;
    const int i = ene_state.iBody;

    body_coors.x = x;
    body_coors.y = y;

    SDL_BlitSurface(g.soldier, &ene_state.ani_arrays->enemyScaredBody[i], g.screen, &body_coors);

    return (EnemyIndexes){11};
}


void soldierCasualArray(SDL_Rect body[12]) {
    body[0].x =    5;   body[0].y =   97;  body[0].w =  34;  body[0].h  = 47;
    body[1].x =   42;   body[1].y =   97;  body[1].w =  34;  body[1].h  = 47;
    body[2].x =   78;   body[2].y =   97;  body[2].w =  34;  body[2].h  = 47;
    body[3].x =  113;   body[3].y =   97;  body[3].w =  34;  body[3].h  = 47;
    body[4].x =    5;   body[4].y =  141;  body[4].w =  34;  body[4].h  = 47;
    body[5].x =   44;   body[5].y =  141;  body[5].w =  34;  body[5].h  = 47;
    body[6].x =   83;   body[6].y =  141;  body[6].w =  34;  body[6].h  = 47;
    body[7].x =  122;   body[7].y =  141;  body[7].w =  34;  body[7].h  = 47;

    body[8].x  =    5;   body[8].y  =  187;  body[8].w  =  34;  body[8].h   = 45;
    body[9].x  =   45;   body[9].y  =  187;  body[9].w  =  34;  body[9].h   = 44;
    body[10].x =   83;   body[10].y =  187;  body[10].w =  34;  body[10].h  = 43;
    body[11].x =  119;   body[11].y =  187;  body[11].w =  34;  body[11].h  = 42;
}

EnemyIndexes soldierCasual(GRAPH g, EnemyState ene_state) {
    SDL_Rect body_coors;

    const int x = ene_state.x;
    const int y = ene_state.y;
    const int i = ene_state.iBody;

    body_coors.x = x;
    body_coors.y = y;

    SDL_BlitSurface(g.soldier, &ene_state.ani_arrays->enemyCasualBody[i], g.screen, &body_coors);

    return (EnemyIndexes){12};
}