# lilengine

lilengine is a game engine written from scratch in C++. It utilizes various APIs to write sprites to a defined window, process keyboard inputs, play sounds, manage game objects via an Entity Component System (ECS),
and run user-written Lua scripts. lilengine is built using the platform [`xmake`](https://xmake.io/). Installation instructions for `xmake` can be found [here](https://xmake.io/#/guide/installation). Once installed, run the command `xmake` on the command line from the lilengine folder to build the system.  

I have created two game demos, one of the classic game Pong, and another of a simple farming game. These game demos can be played by typing either `xmake run pong` or `xmake run farming`. 

# Pong
The Pong demo is a two-player game with the following controls:
  - Pressing `spacebar` begins the game by launching the ball in a randomized direction
  - Player 1 controls the left paddle by pressing `W` to move up and `S` to move down
  - Player 2 controls the right paddle by pressing `Up Arrow` to move up and `Down Arrow` to move down

The score is displayed on the command line.

# Farming
The Farming game demo is a single-player game where the user can move the character around the grassy plain via `WASD`. This demo exemplifies my ability to create a simple Tilemap. The Tilemap Engine is used to
construct and display a randomized Tilemap background for the game.

# APIs
- Window Management and Input Handling: [`GLFW`](https://www.glfw.org/)
- Logging: [`spdlog`](https://github.com/gabime/spdlog)
- Sound: [`SoLoud`](https://solhsa.com/soloud/)
- Graphics: [`sokol_gfx`](https://github.com/floooh/sokol)
- Graphics Mathematics: [`glm`](https://github.com/g-truc/glm)
- Image Loading: [`stb`](https://github.com/nothings/stb)
- Running Lua Scripts: [`sol2`](https://sol2.readthedocs.io/en/latest/api/api-top.html)
