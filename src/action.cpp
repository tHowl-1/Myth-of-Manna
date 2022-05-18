#include "action.h"

using namespace crp;

/*
* TODO - Replace integer codes with an enumerator (probably in it's own header file to include here and in engine.cpp? w/ screen and console size constants)
* Return value means different things:
* 0 = VALID;
* 1 = INVALID;
* 2 = QUIT
* 3 = SWITCH <- requires switch function that returns a new activeHandler
*/

int Action::perform()
{
	return 1; // Always invalid because this is a blank action
}

int MovementAction::perform()
{
	//TODO - Collision checking, return 1 if collides

	// Move player in given direction
	performer->x += dx;
	performer->y += dy;
	return 0;
}

int QuitAction::perform()
{
	// TODO - Add autosaving
	return 2;
}