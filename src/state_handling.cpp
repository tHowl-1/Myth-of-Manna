#include "state_handling.h"

using namespace crp;

// Base
bool BaseHandler::handle_events(SDL_Event* event, Entity* player)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_UP:
            player->y--;// TODO Return action class instead of directly modifying values
            break;
        case SDLK_DOWN:
            player->y++;
            break;
        case SDLK_LEFT:
            player->x--;
            break;
        case SDLK_RIGHT:
            player->x++;
            break;
        default:
            break;
        }
        return false;
    case SDL_QUIT:
        return true;  // Exit
    }
    return false;
}

void BaseHandler::on_render(TileRender* render, Scene* activeScene)
{
    render->draw_entities(activeScene);
	return;
}

