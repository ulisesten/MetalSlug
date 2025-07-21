#ifndef RENDER_H
#define RENDER_H

#include "game.h"
#include "../animation/animation.h"

void renderScenario(ScenarioState* sco_state);
void renderPlayer(PlayerState* state, ScenarioState* sco_state, GRAPH* g);
void renderUpdateCoors(PlayerState* player_state, ScenarioState* sco_state);

#endif