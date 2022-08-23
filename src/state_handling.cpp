#include "state_handling.h"

#include "action.h"
#include "rendering.h"
#include "entity.h"
#include "scene.h"

using namespace mom;

ActionOrHandler* BaseHandler::handle_events(SDL_Event* event, World** activeWorld)
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

void BaseHandler::on_render(TileRender* render, World* activeWorld)
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


ActionOrHandler* MapView::handle_events(SDL_Event* event, World** activeWorld)
{
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) // Check key type
            {
            // Player movement
            case SDLK_UP:
                return newAction(new BumpAction(&(*activeWorld)->player, (*activeWorld)->get_active_map(), 0, -1));
            case SDLK_DOWN:
                return newAction(new BumpAction(&(*activeWorld)->player, (*activeWorld)->get_active_map(), 0, 1));
            case SDLK_LEFT:
                return newAction(new BumpAction(&(*activeWorld)->player, (*activeWorld)->get_active_map(), -1, 0));
            case SDLK_RIGHT:
                return newAction(new BumpAction(&(*activeWorld)->player, (*activeWorld)->get_active_map(), 1, 0));

            case SDLK_g:
                return newAction(new GrabAction(&(*activeWorld)->player, (*activeWorld)->get_active_map()));
            case SDLK_d:
                return newAction(new DumpAction(&(*activeWorld)->player, (*activeWorld)->get_active_map()));

            case SDLK_p:
                return newAction(new SpawnPotionAction(&(*activeWorld)->player, (*activeWorld)->get_active_map()));

            case SDLK_i:
                return newHandler(new InventoryMenu(new MapView));

            case SDLK_SPACE:
                return newAction(new PlaceTileAction(&(*activeWorld)->player, (*activeWorld)->get_active_map()));
            case SDLK_RETURN:
                return newActionHandler(new ExitMapAction(*activeWorld), new WorldView());
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

void MapView::on_render(TileRender* render, World* activeWorld)
{
    render->draw_panel(1, 1, 52, 52);
    render->draw_screen_text("Map", 2, 1);
    render->draw_panel(54, 1, 41, 32);
    render->draw_screen_text("Information", 55, 1);
    render->draw_panel(54, 34, 41, 19);
    render->draw_screen_text("Message Log", 55, 34);
    render->draw_map_tiles(activeWorld->get_active_map(), 0);
    render->draw_entities(activeWorld->get_active_map());
    render->draw_messages(55, 51, 16);
	return;
}

ActionOrHandler* WorldView::handle_events(SDL_Event* event, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
            // Player movement
        case SDLK_UP:
            return newAction(new WorldMovementAction(*activeWorld, 0, -1));
        case SDLK_DOWN:
            return newAction(new WorldMovementAction(*activeWorld, 0, 1));
        case SDLK_LEFT:
            return newAction(new WorldMovementAction(*activeWorld, -1, 0));
        case SDLK_RIGHT:
            return newAction(new WorldMovementAction(*activeWorld, 1, 0));
        case SDLK_r:
            return newActionHandler(new WorldCreateAction(activeWorld, new Params()), new WorldView());
        case SDLK_RETURN:
            return newActionHandler(new EnterMapAction(*activeWorld), new MapView());

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

void WorldView::on_render(TileRender* render, World* activeWorld)
{   
    render->draw_panel(1, 1, 52, 52);
    render->draw_screen_text("World", 2, 1);
    render->draw_panel(54, 1, 41, 32);
    render->draw_screen_text("Information", 55, 1);
    render->draw_panel(54, 34, 41, 19);
    render->draw_screen_text("Message Log", 55, 34);
    render->draw_world_tiles(activeWorld, 0);
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

void Menu::toggleChoice(bool& value)
{
    if (value)
        value = false;
    else
        value = true;
}

void Menu::incrementChoice(float& num, float min, float max, float increment)
{
    if (num + increment > max)
        num = min;
    else if (num + increment < min)
        num = max;
    else
        num += increment;
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

ActionOrHandler* MainMenu::handle_events(SDL_Event* event, World** activeWorld)
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
                return newActionHandler(new WorldCreateAction(activeWorld, new Params()),new NewGame());
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

void MainMenu::on_render(TileRender* render, World* activeWorld)
{
    // TODO - Draw background
    int middle = 10;
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

ActionOrHandler* DebugMenu::handle_events(SDL_Event* event, World** activeWorld)
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

void DebugMenu::on_render(TileRender* render, World* activeWorld)
{
    int middle = 10;
    render->draw_screen_text("Debug Menu", middle, 10);
    return;
}

ActionOrHandler* NewGame::handle_events(SDL_Event* event, World** activeWorld)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym) // Check key type
        {
        case SDLK_UP:
            upChoice(12);
            break;
        case SDLK_DOWN:
            downChoice(12);
            break;
        case SDLK_RETURN:
            switch (choice)
            {
            case 0: // Island Check
                toggleChoice(params.island);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 1: // Polar Check
                toggleChoice(params.polar);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 2: // Rivers Check
                toggleChoice(params.rivers);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 3: // Roads Check
                toggleChoice(params.roads);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 4: // Population Change
                incrementChoice(params.population, 0.6f, 1.5f, 0.20f);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 5: // Temp Change
                incrementChoice(params.temperature, 0.6f, 1.5f, 0.20f);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 6: // Moisture Change
                incrementChoice(params.moisture, 0.6f, 1.5f, 0.20f);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 7: // Roughness Change
                incrementChoice(params.roughness, 0.6f, 1.5f, 0.20f);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 8: // Height Change
                incrementChoice(params.height, 0.6f, 1.5f, 0.20f);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 9: // Sea Level Change
                incrementChoice(params.sealevel, 0.6f, 1.5f, 0.20f);
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 10: // ReRoll
                return newAction(new WorldCreateAction(activeWorld, new Params(params)));
            case 11: // Begin
                return newHandler(new WorldView());
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

void NewGame::on_render(TileRender* render, World* activeWorld)
{
    int middle = 10;
    int x_offset = 18;
    render->draw_panel(1, 1, 41, 52);
    render->draw_panel(43, 1, 52, 52);
    if ((activeWorld) != nullptr)
        render->draw_world_tiles(activeWorld, 42);
    render->draw_screen_text("Preview", 44, 1);
    render->draw_screen_text("Generation", 2, 1);
    render->draw_screen_text("New Game", middle, 8);
    render->draw_screen_text("Island", middle, 12);
    render->draw_check_box(params.island, middle + x_offset, 12);
    render->draw_screen_text("Polar", middle, 14);
    render->draw_check_box(params.polar, middle + x_offset, 14);
    render->draw_screen_text("Rivers", middle, 16);
    render->draw_check_box(params.rivers, middle + x_offset, 16);
    render->draw_screen_text("Roads", middle, 18);
    render->draw_check_box(params.roads, middle + x_offset, 18);
    render->draw_screen_text("Population", middle, 20);
    render->draw_progress_bar(params.population - 0.3f, middle + x_offset - 3, 20, 7);
    render->draw_screen_text("Temperature", middle, 22);
    render->draw_progress_bar(params.temperature - 0.3f, middle + x_offset - 3, 22, 7);
    render->draw_screen_text("Moisture", middle, 24);
    render->draw_progress_bar(params.moisture - 0.3f, middle + x_offset - 3, 24, 7);
    render->draw_screen_text("Roughness", middle, 26);
    render->draw_progress_bar(params.roughness - 0.3f, middle + x_offset - 3, 26, 7);
    render->draw_screen_text("Height", middle, 28);
    render->draw_progress_bar(params.height - 0.3f, middle + x_offset - 3, 28, 7);
    render->draw_screen_text("Sea Level", middle, 30);
    render->draw_progress_bar(params.sealevel - 0.3f, middle + x_offset - 3, 30, 7);
    render->draw_screen_text("Re-Roll", middle, 32);
    render->draw_screen_text("Begin", middle, 34);
    render->draw_menu_marker(choice, middle, 12, 2);
    return;
}

ActionOrHandler* LoadGame::handle_events(SDL_Event* event, World** activeWorld)
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

void LoadGame::on_render(TileRender* render, World* activeWorld)
{
    int middle = render->console->w / 4;
    render->draw_screen_text("Load Game", middle, 10);
    return; // Render nothing
}

ActionOrHandler* MainOptions::handle_events(SDL_Event* event, World** activeWorld)
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

void MainOptions::on_render(TileRender* render, World* activeWorld)
{
    int middle = render->console->w / 4;
    render->draw_screen_text("Options", middle, 10);
    return; // Render nothing
}

ActionOrHandler* PauseMenu::handle_events(SDL_Event* event, World** activeWorld)
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

void PauseMenu::on_render(TileRender* render, World* activeWorld)
{
    parentHandler->on_render(render, activeWorld);
    render->draw_panel(render->console->w / 2 - 8, render->console->h / 2 - 16, 16, 24);
}

ActionOrHandler* InventoryMenu::handle_events(SDL_Event* event, World** activeWorld)
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

void InventoryMenu::on_render(TileRender* render, World* activeWorld)
{
    parentHandler->on_render(render, activeWorld);
    render->draw_panel(54, 1, 41, 32);
    render->draw_screen_text("Inventory", 55, 1);
    render->draw_inventory_list(activeWorld, 56, 3, 20);
}



