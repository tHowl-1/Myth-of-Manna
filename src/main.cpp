#include "main.h"

// Console width and height
const int CON_W = 80, CON_H = 45;
const int SCREEN_W = 1280, SCREEN_H = 720;

// Doom color palette
int doom_colors[36][3] = {
        {7, 7, 7},
        {31, 7, 7},
        {47, 15, 7},
        {71, 15, 7},
        {87, 23, 7},
        {103, 31, 7},
        {119, 31, 7},
        {143, 39, 7},
        {159, 47, 7},
        {175, 63, 7},
        {191, 71, 7},
        {199, 71, 7},
        {223, 79, 7},
        {223, 87, 7},
        {223, 87, 7},
        {215, 95, 7},
        {215, 103, 15},
        {207, 111, 15},
        {207, 119, 15},
        {207, 127, 15},
        {207, 135, 23},
        {199, 135, 23},
        {199, 143, 23},
        {199, 151, 31},
        {191, 159, 31},
        {191, 159, 31},
        {191, 167, 39},
        {191, 167, 39},
        {191, 175, 47},
        {183, 175, 47},
        {183, 183, 47},
        {183, 183, 55},
        {207, 207, 111},
        {223, 223, 159},
        {239, 239, 199},
        {255, 255, 255},
};

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

    // Fire simulation buffer array
    int sim_buffer[CON_W][CON_H] = { 0 }; // 0 = darkest color, 35 = brightest color
    for (int i = 0; i < CON_W; i++)
        sim_buffer[i][CON_H - 1] = 35; // Bottom screen line set to always max brightness

    while (true) {  // Game loop.
        TCOD_console_clear(console.get());

        // Update and render simulation
        for (int x = 0; x < CON_W; x++)
        {
            for (int y = 1; y < CON_H; y++) // y = 1 because top line cannot be pushed to outside buffer
            {
                sim_buffer[std::min(CON_W - 1, std::max(0, x + rand() % 3 - 1))][y - 1] = std::max(0, sim_buffer[x][y] + rand() % 3 - 2);
                console.at({ x, y }).bg = tcod::ColorRGB(doom_colors[sim_buffer[x][y]][0], doom_colors[sim_buffer[x][y]][1], doom_colors[sim_buffer[x][y]][2]);
            }
        }

        context->present(console);  // Updates the visible display.

        SDL_Event event;
        //SDL_WaitEvent(nullptr); //Optional, sleep until events are available.
        while (SDL_PollEvent(&event)) {
            context->convert_event_coordinates(event);  // Optional, converts pixel coordinates into tile coordinates.
            switch (event.type) {
            case SDL_QUIT:
                return 0;  // Exit.
            }
        }
    }
}