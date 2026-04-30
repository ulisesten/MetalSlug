# Metal Slug Clone (SDL2 Game)

Este proyecto es un clon en desarrollo del clásico juego **Metal Slug**, utilizando **C con SDL2**. La estructura está modularizada para facilitar el mantenimiento, pruebas y escalabilidad del código.

---

## 🚀 Características

- Jugador animado con movimiento, salto y disparo.
- Enemigos con IA básica y detección de colisiones.
- Escenario desplazable con múltiples capas.
- Sistema de animaciones separadas para jugador y enemigos.
- Coordinadas de piso leídas desde archivo.

---

### 🧱 Requisitos

- SDL2
- SDL2_image
- CMake ≥ 3.10
- Compilador C compatible (GCC, Clang, MSVC)

---

### 🛠 Compilación
Linux / macOS

- cmake -S . -B build
- cmake --build build
- ./build/metal_slug

Windows
- cmake -S . -B build -G "MinGW Makefiles"
- cmake --build build
- ./build/metal_slug.exe

---

## 🗂 Estructura del Proyecto

```bash
.
├── CMakeLists.txt          # Script de compilación con CMake
├── README.md               # Documentación del proyecto
├── agents/                 # Agentes y habilidades personalizadas
│   └── skills/
├── build/                  # Archivos generados por CMake
├── cmake/                  # Configuración adicional de CMake
│   └── sdl2/               # Scripts de búsqueda para SDL2
├── libs/                   # Librerías incluidas
│   ├── SDL2/               # Librería SDL2
│   └── SDL2_image/         # Extensión SDL2 para imágenes
├── modules/                # Dependencias externas
│   └── socket.io-client-cpp/ # Cliente Socket.IO para C++
├── src/                    # Código fuente del juego
│   ├── main.c              # Punto de entrada del juego
│   ├── animation/          # Módulo de animaciones
│   │   ├── animation.c/h
│   │   ├── animation_enemies.c/h
│   ├── game/               # Lógica principal del juego
│   │   ├── game.c/h
│   ├── init/               # Inicialización del juego
│   │   ├── init.c/h
│   ├── input/              # Captura y manejo de eventos de teclado
│   │   ├── input.c/h
│   ├── render/             # Renderizado de jugador, enemigos y escenario
│   │   ├── floor.c/h
│   │   ├── render.c/h
│   │   ├── render_enemies.c/h
│   ├── resources/          # Recursos gráficos y de coordenadas
│   │   ├── backgrounds/
│   │   ├── coors/          # Archivos .txt con coordenadas del piso
│   │   ├── enemies/
│   │   ├── matrix/
│   │   ├── menu/
│   │   ├── players/
│   └── utils/              # Utilidades generales
│       ├── utils.c/h
└── .gitignore              # Archivos ignorados por Git
```
---

### 🎮 Controles

| Acción   | Tecla             |
| -------- | ----------------- |
| Mover    | Flechas (← → ↑ ↓) |
| Saltar   | Barra espaciadora |
| Disparar | Z                 |
| Salir    | ESC               |

---

### 📁 Recursos

Los recursos están en src/resources/:

- backgrounds/: fondos de escenario
- players/: sprites del jugador
- enemies/: sprites enemigos
- coors/: coordenadas del piso (*.txt)

---

### 📌 Notas de desarrollo

- El archivo game.c contiene la lógica del loop principal y puede refactorizarse aún más para separar lógica del bucle, gestión de estado y renderizado.

- Se recomienda agregar pruebas unitarias para las animaciones y lógica de colisiones en el futuro.

- El código fuente está preparado para una futura migración a escenas múltiples y sistema de menú.

---

### 📄 Licencia

Este proyecto es un clon educativo y no comercial de Metal Slug. No pretende infringir ningún derecho de propiedad intelectual de SNK o sus afiliados.


