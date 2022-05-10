#include <libtcod.hpp> // Necessary for rendering

// Doom color palette
int doom_colors[36][3] = {
        {7, 7, 7},
        {31, 7, 7},
        {47, 15, 7},
        {71, 15, 7},
        {87, 23, 7},
        {103, 31, 7},
        {119, 31, 7},
        {143, 39, 7},
        {159, 47, 7},
        {175, 63, 7},
        {191, 71, 7},
        {199, 71, 7},
        {223, 79, 7},
        {223, 87, 7},
        {223, 87, 7},
        {215, 95, 7},
        {215, 103, 15},
        {207, 111, 15},
        {207, 119, 15},
        {207, 127, 15},
        {207, 135, 23},
        {199, 135, 23},
        {199, 143, 23},
        {199, 151, 31},
        {191, 159, 31},
        {191, 159, 31},
        {191, 167, 39},
        {191, 167, 39},
        {191, 175, 47},
        {183, 175, 47},
        {183, 183, 47},
        {183, 183, 55},
        {207, 207, 111},
        {223, 223, 159},
        {239, 239, 199},
        {255, 255, 255},
};

class Doom_Fire {
    /*
    * 
    *   Basic class to store and render example doom fire simulation:
    * 
    *   -sim_buffer- screen size array to store relative brightness of each fire pixel (0 = darkest color, 35 = brightest color)
    *   -console- reference to active console to ease rendering
    * 
    *   *This could later be upgraded to use a general class that describes many simulations 
    * 
    */
private:
    int sim_buffer[CON_W][CON_H] = { 0 };
    TCOD_Console console;
public:
    Doom_Fire(TCOD_Console& new_console)
    {
        console = new_console;
        for (int i = 0; i < CON_W; i++)
            sim_buffer[i][CON_H - 1] = 35; // Bottom screen line set to always be max brightness
    }

    void update()
    {
        for (int x = 0; x < CON_W; x++)
        {
            for (int y = 1; y < CON_H; y++) // y = 1 because top line cannot be pushed to outside buffer
            {
                sim_buffer[std::min(CON_W - 1, std::max(0, x + rand() % 3 - 1))][y - 1] = std::max(0, sim_buffer[x][y] + rand() % 3 - 2);   // Update simulation
                console.at({ x, y }).bg = tcod::ColorRGB(doom_colors[sim_buffer[x][y]][0], doom_colors[sim_buffer[x][y]][1], doom_colors[sim_buffer[x][y]][2]); // Render simulation using color palette
            }
        }
    }
};