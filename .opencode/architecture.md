# Metal Slug Clone - Architecture Documentation

## Project Overview

**Type:** 2D Action Game (Metal Slug Clone)  
**Language:** C (C99 standard)  
**Graphics Library:** SDL2 + SDL2_image  
**Build System:** CMake (≥ 3.10)  
**Platform:** Cross-platform (Linux, macOS, Windows)

---

## Tech Stack

| Component | Technology |
|-----------|------------|
| Language | C99 |
| Graphics | SDL2 (Simple DirectMedia Layer 2) |
| Image Loading | SDL2_image (PNG support) |
| Build System | CMake |
| Input Handling | SDL2 Joystick/Keyboard API |
| Rendering | SDL2 Hardware-accelerated Renderer |

---

## Directory Structure

```
metal_sulg_c/
├── CMakeLists.txt              # Main build configuration
├── README.md                   # Project documentation
├── .opencode/                  # AI agent configuration
│   └── architecture.md         # This file
├── agents/                     # AI agent skills
│   └── skills/
│       └── .agent.c-developer-expert.md
├── build/                      # CMake build output
├── cmake/                      # CMake modules
│   └── sdl2/                   # SDL2 find modules
├── libs/                       # Third-party libraries
│   ├── SDL2/                   # SDL2 library (vendored)
│   └── SDL2_image/             # SDL2_image library (vendored)
├── modules/                    # External dependencies
│   └── socket.io-client-cpp/   # Socket.IO C++ client (optional multiplayer)
├── src/                        # Game source code
│   ├── main.c                  # Application entry point
│   ├── animation/              # Animation system
│   │   ├── animation.h         # Player state & animation declarations
│   │   ├── animation.c         # Player animation logic
│   │   ├── animation_enemies.h # Enemy animation declarations
│   │   └── animation_enemies.c # Enemy animation logic
│   ├── constants/              # Centralized constants (no magic numbers)
│   │   ├── constants.h         # Aggregator header
│   │   ├── window.h            # Window dimensions
│   │   ├── timers.h            # Animation/scroll tick intervals
│   │   ├── scenario.h          # Scenario parallax/scroll config
│   │   ├── player.h            # Player ranges & shot count
│   │   └── enemies.h           # Enemy proximity & spawn offsets
│   ├── game/                   # Core game logic
│   │   ├── game.h              # Game assets & main function declaration
│   │   └── game.c              # Game loop & state management
│   ├── init/                   # Initialization module
│   │   ├── init.h              # Initialization function declarations
│   │   └── init.c              # Resource loading & entity initialization
│   ├── input/                  # Input handling
│   │   ├── input.h             # Input function declarations
│   │   └── input.c             # Keyboard event processing
│   ├── render/                 # Rendering system
│   │   ├── render.h            # Player/scenario rendering declarations
│   │   ├── render.c            # Player & scenario rendering
│   │   ├── render_enemies.h    # Enemy rendering declarations
│   │   ├── render_enemies.c    # Enemy rendering & collision
│   │   ├── floor.h             # Floor/terrain utilities
│   │   └── floor.c             # Floor coordinate reading & jump trajectory
│   ├── resources/              # Game assets
│   │   ├── backgrounds/        # Background images
│   │   ├── coors/              # Floor coordinates (*.txt)
│   │   ├── enemies/            # Enemy sprite sheets
│   │   ├── matrix/             # Enemy placement data
│   │   │   └── stage_1/
│   │   │       └── enemies.txt
│   │   ├── menu/               # Menu graphics
│   │   └── players/            # Player sprite sheets
│   └── utils/                  # Utility functions
│       ├── utils.h
│       └── utils.c
```

---

## Architectural Patterns

### Module-Based Architecture

The project follows a **modular layered architecture** with clear separation of concerns:

```
┌─────────────────────────────────────────┐
│           main.c (Entry Point)          │
├─────────────────────────────────────────┤
│              game/ (Game Loop)          │
├──────────┬──────────┬─────────┬─────────┤
│ animation│  render  │  input  │  init   │
├──────────┴──────────┴─────────┴─────────┤
│              utils/ (Helpers)           │
└─────────────────────────────────────────┘
```

### Module Responsibilities

| Module | Responsibility |
|--------|----------------|
| **main.c** | SDL2 initialization, window/renderer creation, game launch |
| **game/** | Main game loop, state orchestration, timer updates |
| **animation/** | Frame-by-frame sprite animation logic, timing |
| **render/** | SDL2 rendering calls for all game entities |
| **input/** | SDL2 event polling, keyboard state tracking |
| **init/** | Resource loading, entity initialization, cleanup |
| **constants/** | Centralized naming for all hard-coded values (timers, dimensions, offsets) |
| **utils/** | General helper functions |

---

## Key Components

### 1. Game Loop (`game.c:67-86`)

```c
static void gameLoop(GRAPH* g, GameAssets* assets, PlayerState* player, 
                     EnemyState** enemies, ScenarioState* scenario, 
                     short enemy_count)
```

**Cycle:**
1. Clear renderer
2. Process input (`handleEvents`)
3. Update animation timers
4. Render scenario
5. Render player
6. Update player coordinates
7. Render/update enemies
8. Check collisions
9. Present frame

### 2. State Structures (`animation.h`)

#### PlayerState
```c
typedef struct {
    int x, y, floorIndex;           // Position & terrain index
    int torsoFrame, legsFrame, shootFrame; // Animation frame indices
    int X_RANGE_MAX, X_RANGE_MIN;   // Screen movement range
    int x_displacement;
    int direction, lastDirection;
    bool isMovingBackward, isMovingForward;
    bool shouldBreathe, shouldRun, shouldJump,
         shouldShoot, shouldTranslate, wantToShoot;
    bool keepWalking, shouldUpdateJump;
    bool quit;
    Uint32 lastBreathTick, lastWalkTick, lastJumpTick,
           lastShootTick, lastTranslateTick;
    bool isRunning;
    int shotsRemaining;             // Shot burst counter
    int endOfScenarioOffset;
    bool fullscreen;
    Indexes indexes;                // {maxTorsoFrames, maxLegsFrames}
    AnimationArrays* animations;
    SDL_Texture* textureFront, *textureBack;
} PlayerState;
```

#### ScenarioState
```c
typedef struct {
    SDL_Window* window;
    SDL_Surface* scenario;
    int x, y, w;
    int maxScrollWidth;             // Total scrollable width
    int mountainScrollX;            // Parallax layer positions
    int mountainOffsetCounter;
    int MOUNTAIN_SCROLL_RATIO;      // Foreground px per mountain px
    int SCENARIO_END_OFFSET;
    int horizonScrollX;
    int horizonOffsetCounter;
    int HORIZON_SCROLL_RATIO;
    FloorCoors* floor_coors;
    SDL_Texture* sco_texture;
} ScenarioState;
```

#### EnemyState (animation_enemies.h)
```c
typedef struct {
    short id;
    int x, y, floorIndex;
    int bodyFrame;                  // Current animation frame
    bool shouldAnimate, shouldWalk;
    Uint32 lastAnimateTick, lastWalkTick;
    bool hasReacted;                // Entered SCARED mode at least once
    short spriteVerticalOffset;
    int scenarioScrollOffset;
    short type, mode, direction;
    bool canTransitionMode;         // Allow IA mode change
    AnimationEnemyArrays* animations;
    EnemyIndexes indexes;           // {maxBodyFrames}
    SDL_Texture* texture;
} EnemyState;
```

#### GameAssets (game.h)
```c
typedef struct {
    SDL_Surface *scenarioSurface, *playerSurface,
                *playerBackSurface, *soldierSurface;
} GameAssets;
```

### 3. Animation System

**Frame-based timing:** Each animation state uses `SDL_GetTicks()` to control frame transitions.

**Player animations:**
- `clarkStand` / `clarkStandBack` - Idle poses
- `clarkRun` / `clarkRunBack` - Running cycles
- `clarkShoot` - Shooting frames

**Enemy animations:**
- Generic animate/walk cycles with configurable timing

### 4. Rendering Pipeline

1. **Scenario** - Parallax scrolling with 3 layers (horizon, mountain, foreground)
2. **Player** - Sprite blitting with direction-aware textures
3. **Enemies** - Sprite blitting with collision detection

### 5. Input System (`input.c`)

Handles:
- Arrow keys: Movement (left/right/up/down)
- Space: Jump
- Z key: Shoot
- ESC: Quit

Updates `PlayerState` boolean flags for action states.

### 6. Resource Management

**Loading (`init.c`):**
- `loadResources()` - Loads all assets
- `initPlayer()` - Initializes player state
- `initEnemies()` - Spawns enemies from matrix file
- `initScenario()` - Sets up parallax layers

**Cleanup:**
- `cleanupGame()` - Frees all allocated resources

---

## Data Flow

```
main.c
  │
  ├─ SDL_Init() → Window/Renderer creation
  │
  └─ startGame()
       │
       ├─ loadResources()
       │    ├─ Load sprite sheets
       │    ├─ Read enemy matrix
       │    └─ Read floor coordinates
       │
       ├─ initPlayer() → PlayerState setup
       ├─ initEnemies() → EnemyState[] array
       ├─ initScenario() → ScenarioState setup
       │
       └─ gameLoop()
            │
            ├─ handleEvents() → Update PlayerState flags
            ├─ updateAnimationTimers() → Frame progression
            ├─ render*() → SDL2 draw calls
            └─ collision checks
```

---

## Build & Run

### Linux/macOS
```bash
cmake -S . -B build
cmake --build build
./build/metal_slug
```

### Windows (MinGW)
```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
./build/metal_slug.exe
```

### Dependencies
- SDL2 development libraries
- SDL2_image development libraries (PNG support)

---

## Controls

| Action | Key |
|--------|-----|
| Move | Arrow Keys (← → ↑ ↓) |
| Jump | Space |
| Shoot | Z |
| Quit | ESC |

---

## Known Technical Debt

1. **game.c** - Contains game loop logic; could be further refactored for state management separation
2. **No unit tests** - Animation and collision logic lacks test coverage
3. **Single scene** - No multi-scene or menu system implemented
4. **Hardcoded paths** - Resource paths are string literals
5. **Memory management** - Manual malloc/free; no centralized resource manager

---

## Future Architecture Considerations

- **Entity Component System (ECS)** for scalable game objects
- **Scene manager** for multiple levels/menus
- **Asset manager** with reference counting
- **State machine** for player/enemy behaviors
- **Configuration files** for game balance tuning
- **Network layer** using socket.io-client-cpp for multiplayer

---

## AI Agent Guidelines

When working with this codebase:

1. **Respect module boundaries** - Keep animation logic in `animation/`, rendering in `render/`, etc.
2. **Follow C99 conventions** - Use existing naming patterns (snake_case, descriptive names)
3. **SDL2 error handling** - Always check return values and log with `SDL_GetError()`
4. **Memory safety** - Pair every `malloc` with `free`, prefer stack allocation when possible
5. **Animation timing** - Use `SDL_GetTicks()` for frame-independent timing
6. **CMake changes** - Update `CMakeLists.txt` when adding new source files
7. **Test builds** - Always verify compilation after changes
8. **No magic numbers** - All hard-coded values must be named macros in `src/constants/`. Use the thematic headers: `window.h`, `timers.h`, `scenario.h`, `player.h`, `enemies.h`. Include them via `#include "constants/xxx.h"` (path is in CMake include_directories). When a struct field shares the macro's name, append `_VALUE` to the macro to avoid collisions in designated initializers (e.g., `.MOUNTAIN_SCROLL_RATIO = MOUNTAIN_SCROLL_RATIO_VALUE`).
9. **State members** - Names are descriptive (`torsoFrame`, `shouldBreathe`, `lastBreathTick`, `isMovingForward`, `floorIndex`, `textureFront`). Avoid reverting to cryptic names like `iTorso`, `pastBreath`, `IS_RUNNING_FORWARD`, `h`, `pla_texture`. Dead/unused members were removed (`x_move_range`, `iS`, `direccion`, `key_up`, `key_down`).

---

## Related Documentation

- [README.md](../README.md) - User-facing documentation
- [C Developer Expert Agent](../agents/skills/.agent.c-developer-expert.md) - AI agent configuration for C development