#pragma once

// 16:9 aspect ratio, console/screem width and height in cells/pixels respectively - TODO Move constants into some engine class
const int CON_W = 80, CON_H = 45; 
const int SCREEN_W = 1280, SCREEN_H = 720;

// Standard
#include <iostream>

// libtcod
#include <libtcod.hpp>
#include <SDL2/SDL.h>

// Engine
#include "doom_fire.h"