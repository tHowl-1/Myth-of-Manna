#include "state_handling.h"

using namespace mom;

ActionOrHandler* BaseHandler::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_ESCAPE:
            return newHandler(new MainMenu());
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

void BaseHandler::on_render(TileRender* render, World* activeWorld, Entity* player)
{
    return; // Render nothing
}

ActionOrHandler* BaseHandler::newHandler(BaseHandler* handler)
{
    ActionOrHandler* newHandler = new ActionOrHandler();
    newHandler->handler = handler;
    newHandler->isAction = false;
    newHandler->isHandler = true;
    return newHandler;
}

ActionOrHandler* BaseHandler::newAction(Action* action)
{
    ActionOrHandler* newAction = new ActionOrHandler();
    newAction->action = action;
    newAction->isAction = true;
    newAction->isHandler = false;
    return newAction;
}

ActionOrHandler* BaseHandler::newActionHandler(Action* action, BaseHandler* handler)
{
    ActionOrHandler* newActionHandler = new ActionOrHandler();
    newActionHandler->action = action;
    newActionHandler->handler = handler;
    newActionHandler->isAction = true;
    newActionHandler->isHandler = true;
    return newActionHandler;
}


ActionOrHandler* MapView::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) // Check key type
            {
            // Player movement
            case SDLK_UP:
                return newAction(new BumpAction(player, (*activeWorld)->get_active_map(), 0, -1));
            case SDLK_DOWN:
                return newAction(new BumpAction(player, (*activeWorld)->get_active_map(), 0, 1));
            case SDLK_LEFT:
                return newAction(new BumpAction(player, (*activeWorld)->get_active_map(), -1, 0));
            case SDLK_RIGHT:
                return newAction(new BumpAction(player, (*activeWorld)->get_active_map(), 1, 0));

            case SDLK_SPACE:
                return newAction(new PlaceTileAction(player, (*activeWorld)->get_active_map()));
            case SDLK_RETURN:
                return newActionHandler(new ExitMapAction((*activeWorld)->playerParty, *activeWorld), new WorldView());
            case SDLK_ESCAPE:
                return newHandler(new PauseMenu(new MapView));
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

void MapView::on_render(TileRender* render, World* activeWorld, Entity* player)
{
    render->draw_panel(1, 1, 52, 52);
    render->draw_screen_text("Map", 2, 1);
    render->draw_panel(54, 1, 41, 32);
    render->draw_screen_text("Information", 55, 1);
    render->draw_panel(54, 34, 41, 19);
    render->draw_screen_text("Message Log", 55, 34);
    render->draw_map_tiles(activeWorld->get_active_map());
    render->draw_entities(activeWorld->get_active_map());
    render->draw_messages(55, 51, 16);
	return;
}

ActionOrHandler* WorldView::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
            // Player movement
        case SDLK_UP:
            return newAction(new WorldMovementAction((*activeWorld)->playerParty, *activeWorld, 0, -1));
        case SDLK_DOWN:
            return newAction(new WorldMovementAction((*activeWorld)->playerParty, *activeWorld, 0, 1));
        case SDLK_LEFT:
            return newAction(new WorldMovementAction((*activeWorld)->playerParty, *activeWorld, -1, 0));
        case SDLK_RIGHT:
            return newAction(new WorldMovementAction((*activeWorld)->playerParty, *activeWorld, 1, 0));
        case SDLK_r:
            return newActionHandler(new WorldCreateAction(activeWorld, nullptr), new WorldView());
        case SDLK_RETURN:
            return newActionHandler(new EnterMapAction((*activeWorld)->playerParty, *activeWorld), new MapView());

        case SDLK_ESCAPE:
            return newHandler(new PauseMenu(new WorldView));
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

void WorldView::on_render(TileRender* render, World* activeWorld, Entity* player)
{   
    render->draw_panel(1, 1, 52, 52);
    render->draw_screen_text("World", 2, 1);
    render->draw_panel(54, 1, 41, 32);
    render->draw_screen_text("Information", 55, 1);
    render->draw_panel(54, 34, 41, 19);
    render->draw_screen_text("Message Log", 55, 34);
    render->draw_world_tiles(activeWorld);
    render->draw_parties(activeWorld);
    render->draw_messages(55, 51, 16);
    return;
}

void Menu::upChoice(int numChoices)
{
    choice--;
    if (choice < 0)
        choice = numChoices - 1;
}

void Menu::downChoice(int numChoices)
{
    choice++;
    if (choice > numChoices - 1)
        choice = 0;
}

// Menu Templates
/*
case SDLK_UP:
    upChoice(1);
    break;
case SDLK_DOWN:
    downChoice(1);
    break;
case SDLK_RETURN:
    switch (choice)
    {
    case 0: // <- MENU OPTIONS HERE
        break;
    default:
        break;
    }
    break;
default:
    break;
  */

ActionOrHandler* MainMenu::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_UP:
            upChoice(4);
            break;
        case SDLK_DOWN:
            downChoice(4);
            break;
        case SDLK_RETURN:
            switch (choice)
            {
            case 0: // NEW
                return newHandler(new NewGame());
            case 1: // LOAD
                return newHandler(new LoadGame());
            case 2: // OPTIONS
                return newHandler(new MainOptions());
            case 3: // QUIT
                return newAction(new QuitAction());
            default:
                break;
            }
            break;
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

void MainMenu::on_render(TileRender* render, World* activeWorld, Entity* player)
{
    // TODO - Draw background
    int middle = render->console->w / 4;
    render->draw_screen_text("Main Menu", middle, 10);
    render->draw_screen_text("New", middle, 12);
    render->draw_screen_text("Load", middle, 14);
    render->draw_screen_text("Options", middle, 16);
    render->draw_screen_text("Quit", middle, 18);
    render->draw_menu_marker(choice, middle, 12, 2);
    return;
}

void DebugMenu::toggleDebug(int index)
{
   // Find render bool value to modify
   /* if (*value)
        *value = false;
    else
        *value = true;*/
    return;
}

ActionOrHandler* DebugMenu::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{

    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_UP:
            upChoice(1);
            break;
        case SDLK_DOWN:
            downChoice(1);
            break;
        case SDLK_RETURN:
            switch (choice)
            {
            case 0: // <- MENU OPTIONS HERE
                break;
            default:
                break;
            }
            break;
        case SDLK_ESCAPE:
            return newHandler(new WorldView());
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

void DebugMenu::on_render(TileRender* render, World* activeWorld, Entity* player)
{
    int middle = render->console->w / 4;
    render->draw_screen_text("Debug Menu", middle, 10);
    return;
}

ActionOrHandler* NewGame::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_UP:
            upChoice(1);
            break;
        case SDLK_DOWN:
            downChoice(1);
            break;
        case SDLK_RETURN:
            switch (choice)
            {
            case 0: // Generate
                return newActionHandler(new WorldCreateAction(activeWorld, nullptr), new WorldView()); // TODO : Parameter creation and modification in handler
            default:
                break;
            }
            break;
        case SDLK_ESCAPE:
            return newHandler(new MainMenu());
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

void NewGame::on_render(TileRender* render, World* activeWorld, Entity* player)
{
    int middle = render->console->w / 4;
    render->draw_screen_text("New Game", middle, 10);
    render->draw_screen_text("Generate", middle, 12);
    render->draw_menu_marker(choice, middle, 12, 2);
    return;
}

ActionOrHandler* LoadGame::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_UP:
            upChoice(1);
            break;
        case SDLK_DOWN:
            downChoice(1);
            break;
        case SDLK_RETURN:
            switch (choice)
            {
            case 0: // <- MENU OPTIONS HERE
                break;
            default:
                break;
            }
            break;
        case SDLK_ESCAPE:
            return newHandler(new MainMenu());
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

void LoadGame::on_render(TileRender* render, World* activeWorld, Entity* player)
{
    int middle = render->console->w / 4;
    render->draw_screen_text("Load Game", middle, 10);
    return; // Render nothing
}

ActionOrHandler* MainOptions::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_UP:
            upChoice(1);
            break;
        case SDLK_DOWN:
            downChoice(1);
            break;
        case SDLK_RETURN:
            switch (choice)
            {
            case 0: // <- MENU OPTIONS HERE
                break;
            default:
                break;
            }
            break;
        case SDLK_ESCAPE:
            return newHandler(new MainMenu());
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

void MainOptions::on_render(TileRender* render, World* activeWorld, Entity* player)
{
    int middle = render->console->w / 4;
    render->draw_screen_text("Options", middle, 10);
    return; // Render nothing
}

ActionOrHandler* PauseMenu::handle_events(SDL_Event* event, Entity* player, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_UP:
            upChoice(1);
            break;
        case SDLK_DOWN:
            downChoice(1);
            break;
        case SDLK_RETURN:
            switch (choice)
            {
            case 0: // <- MENU OPTIONS HERE
                break;
            default:
                break;
            }
            break;
        case SDLK_ESCAPE:
            return newHandler(parentHandler);
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

void PauseMenu::on_render(TileRender* render, World* activeWorld, Entity* player)
{
    parentHandler->on_render(render, activeWorld, player);
    render->draw_panel(render->console->w / 2 - 8, render->console->h / 2 - 16, 16, 24);
}
