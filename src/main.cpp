// Libtcod
#include <libtcod.hpp>
#include <SDL2/SDL.h>

// Engine
#include "engine.h"

using namespace crp;

int main(int argc, char* argv[]) {
    Engine engine;
    while (!engine.QUIT_FLAG) // Game loop
        engine.update();
    return 0;
}