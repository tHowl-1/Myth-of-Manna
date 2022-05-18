#pragma once

// Forward Declarations
class Scene;

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "entity.h"
#include "render.h"
#include "action.h"

namespace crp
{
	// Game state handler. including: render state, input handling
	class BaseHandler
	{
	public:
		virtual Action* handle_events(SDL_Event* event, Entity* player);

		virtual void on_render(TileRender* render, Scene* activeScene);
	};

	// Basic movement and gameplay TODO - Rename and specify later
	class MainGameHandler : public BaseHandler
	{
	public:
		Action* handle_events(SDL_Event* event, Entity* player);

		void on_render(TileRender* render, Scene* activeScene);
	};

	// The game's main menu / title screen
	class MainMenuHandler : public BaseHandler
	{
	public:
		Action* handle_events(SDL_Event* event, Entity* player);

		void on_render(TileRender* render, Scene* activeScene);
	};
}