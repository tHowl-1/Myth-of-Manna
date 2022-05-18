#include "palette.h"

#include "engine.h"

using namespace crp;

Engine::Engine()
{
	// Configure the context
	auto params = TCOD_ContextParams{};
	params.tcod_version = TCOD_COMPILEDVERSION;  // This is required
	params.window_title = "Collaborative Roguelike Project";
	params.pixel_width = SCREEN_W;
	params.pixel_height = SCREEN_H;
	params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
	params.vsync = true;
	params.renderer_type = TCOD_RENDERER_SDL2; // Render using SDL2

	// Tileset example using a Code Page 437 font
	tileset = tcod::load_tilesheet("16x16-sb-ascii.png", { 16, 16 }, tcod::CHARMAP_CP437); // FIXME: This assumes the tileset is located in the same directory as the .exe
	params.tileset = tileset.get();

	console = tcod::Console{ CON_W, CON_H };  // Main console
	params.console = console.get();  // Derive the window size from the console size
	
	context = tcod::new_context(params);

	player = new Entity(CON_W / 2, CON_H / 2, "☺", WHITE);
	render = new TileRender(console.get());
	activeHandler = new BaseHandler();
	activeScene = new Scene(player);
}

void Engine::update()
{
	activeHandler->on_render(render, activeScene);
	context->present(console);

	TCOD_console_clear(console.get());
	SDL_Event event;
	//SDL_WaitEvent(nullptr); //Optional, sleep until events are available WARNING This will cause pausing in the doom fire simulation!
	while (SDL_PollEvent(&event)) {
		context->convert_event_coordinates(event);  // Optional, converts pixel coordinates into tile coordinates
		QUIT = activeHandler->handle_events(&event, player);
	}
}