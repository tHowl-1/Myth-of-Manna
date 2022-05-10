#include "main.h"

int main(int argc, char* argv[]) {
    // Configure the context.
    auto params = TCOD_ContextParams{};
    params.tcod_version = TCOD_COMPILEDVERSION;  // This is required.
    params.window_title = "Collaborative Roguelike Project";
    params.pixel_width = SCREEN_W;
    params.pixel_height = SCREEN_H;
    params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
    params.vsync = true;
    params.renderer_type = TCOD_RENDERER_SDL2; // Render using SDL2
    params.argc = argc;  // This allows some user-control of the context.
    params.argv = argv;

    // Tileset example using a Code Page 437 font.
    auto tileset = tcod::load_tilesheet("16x16-sb-ascii.png", { 16, 16 }, tcod::CHARMAP_CP437); // FIXME: This assumes the tileset is located in the same directory as the .exe

    auto console = tcod::Console{ CON_W, CON_H };  // Main console.
    params.console = console.get();  // Derive the window size from the console size.

    auto context = tcod::new_context(params);

    // FIXME : delete later
    Doom_Fire simulation(console);
    int player_x = CON_W / 2, player_y = CON_H / 2;
    
    while (true) {  // Game loop.
        TCOD_console_clear(console.get());

        //simulation.update() // update doom fire

        // render player
        tcod::print(console, { player_x, player_y }, "@", { {255, 255, 255} }, { {0, 0, 0} });

        context->present(console);  // Updates the visible display.

        SDL_Event event;
        SDL_WaitEvent(nullptr); //Optional, sleep until events are available.
        while (SDL_PollEvent(&event)) {
            context->convert_event_coordinates(event);  // Optional, converts pixel coordinates into tile coordinates.
            switch (event.type) {
            case SDL_KEYDOWN: // key pressed
                switch (event.key.keysym.sym) // check key type
                {
                case SDLK_UP:
                    player_y--;
                    break;
                case SDLK_DOWN:
                    player_y++;
                    break;
                case SDLK_LEFT: 
                    player_x--;
                    break;
                case SDLK_RIGHT:
                    player_x++;
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT:
                return 0;  // Exit.
            }
        }
    }
}