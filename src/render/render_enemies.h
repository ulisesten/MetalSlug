#ifndef __RENDER_ENEMIES__
#define __RENDER_ENEMIES__

#include "../animation/animation_enemies.h"

void renderEnemies(EnemyState* ene_states, GRAPH* g);
void renderUpdateEnemyCoors( EnemyState* ene_state, PlayerState* pla_state, ScenarioState* sco_state );
void renderEnemyCollisions( EnemyState* ene_state, PlayerState* pla_state, ScenarioState* sco_state );

#endif //__RENDER_ENEMIES__