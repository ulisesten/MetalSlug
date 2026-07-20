#ifndef RENDER_H
#define RENDER_H

#include "game.h"
#include "../animation/animation_player_clark.h"
#include "../animation/animation_enemies.h"

void renderScenario(GRAPH* g, ScenarioState* sco_state);
void renderPlayer(PlayerState* state, ScenarioState* sco_state, GRAPH* g);
void renderUpdateCoors(PlayerState* player_state, ScenarioState* sco_state);
void renderBullets(GRAPH* g, BulletPool* pool);

/* Toggleable debug overlay (F1). Draws AABB outlines of player torso/legs
 * (red/cyan) and each live enemy body (yellow). */
void renderDebugRects(GRAPH* g, PlayerState* pla, EnemyState** enemies, int enemy_count);

#endif