#include "state_handling.h"

using namespace crp;

// Base
Action* BaseHandler::handle_events(SDL_Event* event, Entity* player)
{
    return new Action(); // Always invalid
}

void BaseHandler::on_render(TileRender* render, Scene* activeScene)
{
    return; // Render nothing
}

// MainGame
Action* MainGameHandler::handle_events(SDL_Event* event, Entity* player)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) // Check key type
            {
            // Player movement
            case SDLK_UP:
                return new MovementAction(player, 0, -1);
            case SDLK_DOWN:
                return new MovementAction(player, 0, 1);
            case SDLK_LEFT:
                return new MovementAction(player, -1, 0);
            case SDLK_RIGHT:
                return new MovementAction(player, 1, 0);

            case SDLK_ESCAPE:
                return new QuitAction();
            default:
                break;
            }
            break;
        case SDL_QUIT: // Exit the program on window close
            return new QuitAction();
        default:
            break;
    }
    return new Action(); // Return invalid blank action
}

void MainGameHandler::on_render(TileRender* render, Scene* activeScene)
{
    render->draw_entities(activeScene);
	return;
}

// MainMenu
Action* MainMenuHandler::handle_events(SDL_Event* event, Entity* player)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        // TODO - Add menu options

        case SDLK_ESCAPE:
            return new QuitAction();
        default:
            break;
        }
        break;
    case SDL_QUIT: // Exit the program on window close
        return new QuitAction();
    default:
        break;
    }
    return new Action(); // Return invalid blank action
}

void MainMenuHandler::on_render(TileRender* render, Scene* activeScene)
{
    // TODO - Draw background
    // TODO - Draw menu text options (new, load, options, quit)
    return;
}
