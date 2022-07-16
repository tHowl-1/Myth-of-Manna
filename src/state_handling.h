#pragma once

// Forward Declarations
class Map;

// Dependancies
#include <libtcod.hpp>
#include <SDL2/SDL.h>
#include <map>
#include <iostream>

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
		virtual ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		virtual void on_render(TileRender* render, World* activeWorld, Entity* player);

		virtual ~BaseHandler() {}
	protected:
		ActionOrHandler* newHandler(BaseHandler* handler);

		ActionOrHandler* newAction(Action* action);

		ActionOrHandler* newActionHandler(Action* action, BaseHandler* handler);
	};
	
	// Union with action to provide allow changing active handler or returning an action or both
	struct ActionOrHandler
	{
		bool isAction;
		bool isHandler;
		Action* action;
		BaseHandler* handler;
	};

	// Map gameplay
	class MapView : public BaseHandler
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		void on_render(TileRender* render, World* activeWorld, Entity* player);
	};

	class WorldView : public BaseHandler
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		void on_render(TileRender* render, World* activeWorld, Entity* player);
	};

	// Secondary Classes
	// Handler with option handling
	class Menu : virtual public BaseHandler
	{
	public:
		virtual ~Menu() {}
	protected:
		int choice = 0;

		void upChoice(int numChoices);

		void downChoice(int numChoices);
	};

	// Overlays another handler
	class Overlay : virtual public BaseHandler
	{
	public:
		Overlay(BaseHandler* parent) : parentHandler(parent) {}

		virtual ~Overlay() {}
	protected:
		BaseHandler* parentHandler;
	};

	// Tertiary Classes
	// Overlay and menu
	class PopUpMenu : public Overlay, public Menu 
	{
	public:
		PopUpMenu(BaseHandler* parent) : Overlay(parent) {}

		virtual ~PopUpMenu() {}
	};

	// The game's main menu / title screen
	class MainMenu : public Menu
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		void on_render(TileRender* render, World* activeWorld, Entity* player);
	};	

	class DebugMenu : public Menu
	{
	private:
		void toggleDebug(int index);
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		void on_render(TileRender* render, World* activeWorld, Entity* player);
	};

	class NewGame : public Menu
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		void on_render(TileRender* render, World* activeWorld, Entity* player);
	};

	class LoadGame : public Menu
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		void on_render(TileRender* render, World* activeWorld, Entity* player);
	};

	class MainOptions : public Menu
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		void on_render(TileRender* render, World* activeWorld, Entity* player);
	};

	class PauseMenu : public PopUpMenu
	{
	public:
		ActionOrHandler* handle_events(SDL_Event* event, Entity* player, World** activeWorld);

		void on_render(TileRender* render, World* activeWorld, Entity* player);

		PauseMenu(BaseHandler* parent) : PopUpMenu(parent) {}
	};
}
