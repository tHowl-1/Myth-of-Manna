# Myth-of-Manna
A simple libtcod project to learn about managing a large project.

The goal of this project was to learn about how to organize large object oriented projects and to gain practice coding in c++. Ultimately, I think all around some parts of the code are rough and could use more work but I have learned a lot since starting about what to do and what not to do.

Here are a few pictures showing variation in world map generation featuring different biomes and heights using layered noisemaps

![WorldGen](https://github.com/tHowl-1/Myth-of-Manna/blob/master/pics/world1.PNG?raw = true "An example of world generation")

![WorldGen](https://github.com/tHowl-1/Myth-of-Manna/blob/master/pics/world2.PNG?raw = true "An example of world generation")

![WorldGen](https://github.com/tHowl-1/Myth-of-Manna/blob/master/pics/world3.PNG?raw = true "An example of world generation")

Includes basic world generation, movement, collisions, and action handling for a simple roguelike. dditionally, entity interactions are handled using a component and event system. Rendering is handled using libtcod and prints ascii characters onto the console. The game also features a newly added inventory system.

Each character represents a biome that can be opened and visited. Each tile is procedurally generated and persistent.

![BiomeGen](https://github.com/tHowl-1/Myth-of-Manna/blob/master/pics/snowy.PNG?raw = true "An example of biome generation")

![BiomeGen](https://github.com/tHowl-1/Myth-of-Manna/blob/master/pics/rocky.PNG?raw = true "An example of biome generation")

![BiomeGen](https://github.com/tHowl-1/Myth-of-Manna/blob/master/pics/jungle%2Binventory.PNG?raw = true "An example of biome generation")

