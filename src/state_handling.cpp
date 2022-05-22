#include "state_handling.h"

using namespace crp;

// Base
ActionOrHandler* BaseHandler::handle_events(SDL_Event* event, Entity* player, GameMap* activeScene)
{
    ActionOrHandler* action = new ActionOrHandler();
    action->actionOrHandler.action = new Action();
    action->isAction = true;
    return action; // always invalid
}

void BaseHandler::on_render(TileRender* render, GameMap* activeScene)
{
    return; // Render nothing
}

ActionOrHandler* BaseHandler::newHandler(BaseHandler* handler)
{
    ActionOrHandler* newAction = new ActionOrHandler();
    newAction->actionOrHandler.handler = handler;
    newAction->isAction = false;
    return newAction;
}

ActionOrHandler* BaseHandler::newAction(Action* action)
{
    ActionOrHandler* newAction = new ActionOrHandler();
    newAction->actionOrHandler.action = action;
    newAction->isAction = true;
    return newAction;
}


// MainGame
ActionOrHandler* MainGameHandler::handle_events(SDL_Event* event, Entity* player, GameMap* activeScene)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) // Check key type
            {
            // Player movement
            case SDLK_UP:
                return newAction(new MovementAction(player, activeScene, 0, -1));
            case SDLK_DOWN:
                return newAction(new MovementAction(player, activeScene, 0, 1));
            case SDLK_LEFT:
                return newAction(new MovementAction(player, activeScene, -1, 0));
            case SDLK_RIGHT:
                return newAction(new MovementAction(player, activeScene, 1, 0));

            case SDLK_KP_8:
                return newAction(new CameraMovementAction(player, activeScene, 0, -1));
            case SDLK_KP_2:
                return newAction(new CameraMovementAction(player, activeScene, 0, 1));
            case SDLK_KP_4:
                return newAction(new CameraMovementAction(player, activeScene, -1, 0));
            case SDLK_KP_6:
                return newAction(new CameraMovementAction(player, activeScene, 1, 0));

            case SDLK_KP_5:
                return newAction(new CameraLockAction(player, activeScene));

            case SDLK_ESCAPE:
                return newHandler(new MainMenuHandler());
            default:
                break;
            }
            break;
        case SDL_QUIT: // Exit the program on window close
            return newAction(new QuitAction());
        default:
            break;
    }
    return newAction(new Action()); // Return invalid blank action
}

void MainGameHandler::on_render(TileRender* render, GameMap* activeScene)
{
    render->draw_tiles(activeScene);
    render->draw_entities(activeScene);
    render->draw_text("Game", 0, 0);
	return;
}

// MainMenu
ActionOrHandler* MainMenuHandler::handle_events(SDL_Event* event, Entity* player, GameMap* activeScene)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        // TODO - Add menu options

        case SDLK_ESCAPE:
            return newHandler(new MainGameHandler());
        default:
            break;
        }
        break;
    case SDL_QUIT: // Exit the program on window close
        return newAction(new QuitAction());
    default:
        break;
    }
    return newAction(new Action()); // Return invalid blank action
}

void MainMenuHandler::on_render(TileRender* render, GameMap* activeScene)
{
    // TODO - Draw background
    // TODO - Draw menu text options (new, load, options, quit)
    render->draw_text("Main Menu", 0, 0);
    return;
}

