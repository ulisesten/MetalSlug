#ifndef RENDER_H
#define RENDER_H

#include "game.h"
#include "../animation/animation_player_clark.h"

void renderScenario(GRAPH* g, ScenarioState* sco_state);
void renderPlayer(PlayerState* state, ScenarioState* sco_state, GRAPH* g);
void renderUpdateCoors(PlayerState* player_state, ScenarioState* sco_state);
void renderBullets(GRAPH* g, BulletPool* pool);

#endif