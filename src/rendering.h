#pragma once


// Dependancies
#include <string>
#include <libtcod.hpp>
#include "cp_437.h"
#include "entity.h"
#include "scene.h"

const int MAP_OFFSET = 2;

namespace mom
{
	struct ColorHSV
	{
		float hue;
		float sat;
		float val;
	public:
		ColorHSV(float H, float S, float V) : hue(H), sat(S), val(V) {}
	};

	// 2D Tile Renderer
	class TileRender
	{
	public:
		// Pointer to active console to draw onto
		TCOD_Console* console;

		TileRender(TCOD_Console* console) : console(console){};

		// MAIN DRAWING FEATURES

		// Draws map entities
		void draw_entities(Map* map);
		// Draws world parties
		void draw_parties(World* world);

		// Draws map tiles
		void draw_map_tiles(Map* map, int offset);
		// Draws world tiles
		void draw_world_tiles(World* world, int offset);

		// Draws text at screen coords
		void draw_screen_text(std::string text, int x, int y);
		// Draws text at world coords
		void draw_world_text(std::string text, int x, int y);

		// Menu Stuff
		// Draws menu position
		void draw_menu_marker(int choice, int x, int y, int offset);

		void draw_check_box(bool value, int x, int y);

		void draw_progress_bar(float value, int x, int y, int w);

		void draw_panel(int x, int y, int w, int h);

		void draw_messages(int x, int y, int h);

	};
}