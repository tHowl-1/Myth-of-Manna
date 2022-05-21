#pragma once

// Forward Declarations
class GameMap;

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>

#include "entity.h"
#include "render.h"
#include "action.h"

namespace crp
{
	// Game state handler. including: render state, input handling
	struct ActionOrHandler;

	class BaseHandler
	{
	public:
		virtual ActionOrHandler* handle_events(SDL_Event* event, Entity* player, GameMap* activeScene);

		virtual void on_render(TileRender* render, GameMap* activeScene);
	protected:
		ActionOrHandler* newHandler(BaseHandler* handler);

		ActionOrHandler* newAction(Action* action);
	};

	// Union with action to provide allow changing active handler or returning an action
	union ActionOrHandlerUnion
	{
		Action* action;
		BaseHandler* handler;
	};

	struct ActionOrHandler
	{
		bool isAction;
		ActionOrHandlerUnion actionOrHandler;
	};

	// Basic movement and gameplay TODO - Rename and specify later
	class MainGameHandler : public BaseHandler
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, GameMap* activeScene);

		void on_render(TileRender* render, GameMap* activeScene);
	};

	// The game's main menu / title screen
	class MainMenuHandler : public BaseHandler
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, GameMap* activeScene);

		void on_render(TileRender* render, GameMap* activeScene);
	};	
}
