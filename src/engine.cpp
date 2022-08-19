#include "palette.h"
#include <exception>
#include "logging.h"

#include "engine.h"


using namespace mom;

Engine::Engine()
{
	// Configure the context
	auto params = TCOD_ContextParams{};
	params.tcod_version = TCOD_COMPILEDVERSION;
	params.window_title = "Myth of Manna";
	params.pixel_width = SCREEN_W;
	params.pixel_height = SCREEN_H;
	params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
	params.vsync = true;
	params.renderer_type = TCOD_RENDERER_SDL2;

	// Tileset example using a Code Page 437 font
	tileset = tcod::load_tilesheet("16x16-sb-ascii.png", { 16, 16 }, tcod::CHARMAP_CP437); // FIXME - This assumes the tileset is located in the same directory as the .exe
	params.tileset = tileset.get();

	console = tcod::Console{ CON_W, CON_H };
	params.console = console.get();  // DELETE - Possibly unnecessary, pls confirm

	context = tcod::new_context(params);

	viewportOptions.keep_aspect = true;
	viewportOptions.integer_scaling = true;
	viewportOptions.clear_color = { 0, 0, 0, 255 };
	viewportOptions.align_x = 0.5f;
	viewportOptions.align_y = 0.5f;
	
	render = new TileRender(console.get());
	activeHandler = new MainMenu();
	activeWorld = new World(); // Blank world
}

Engine::~Engine()
{
	delete render;
	delete activeHandler;
	delete activeWorld;
}

// TODO - Make private (along with everything else in this project that can be and add getters and setters if needed)
void Engine::validate_action(ActionOrHandler* actionOrHandler)
{
	if (actionOrHandler->isAction) // Action
	{
		try
		{
			switch (actionOrHandler->action->perform()) // Perform Action
			{
			case Validate::VALID:
				// TODO - ai moves here
				break;
			case Validate::INVALID:
				break;
			case Validate::QUIT: // Quit
				QUIT_FLAG = true;
				break;
			default:
				break;
			}
		}
		catch (std::exception& e)
		{
			std::string errorMessage = e.what();
			MessageLog::getInstance().writeMessage("Exception: " + errorMessage, RED);
		}
		delete actionOrHandler->action;
	}
	if (actionOrHandler->isHandler) // Handler
	{
		delete activeHandler;
		activeHandler = actionOrHandler->handler; // Swap handler
	}
	delete actionOrHandler;
}

void Engine::update()
{
	activeHandler->on_render(render, activeWorld);
	context->present(console, viewportOptions);
	TCOD_console_clear(console.get());
	SDL_Event event;
	SDL_WaitEvent(nullptr); //Optional, sleep until events are available (WARNING This is probably the source of pausing in realtime rendering)
	while (SDL_PollEvent(&event)) {
		context->convert_event_coordinates(event);  // Optional, converts pixel coordinates into tile coordinates (useful for mouse events)
		validate_action(activeHandler->handle_events(&event, &activeWorld));
	}
}