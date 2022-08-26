# Myth-of-Manna
A long term C++ libtcod roguelike game project to learn more about managing a large project.

BUILD:

Builds using CMake requires libtcod to run. It can be downloaded using vcpkg and built on visual studio.

PURPOSE:

The goal of this project was to learn about how to organize large object oriented projects and to gain practice coding in c++. Ultimately, I think all around some parts of the code are rough and could use a lot more work but I have learned a lot since starting this project. All code was written by me and is my original work. I have taken program architecture inspiration from a variety of sources including the python tcod tutorial project and a few online talks by game developers.

A few things I implemented are:
Singleton - Message logging to ingame console
Event and component system - to allow large variation and interesting behavior in game actions
State Handling - couples game state and rendering


FEATURES:

Includes basic world generation, movement, collisions, and action handling for a simple roguelike. dditionally, entity interactions are handled using a component and event system. Rendering is handled using libtcod and prints ascii characters onto the console. The game also features a newly added inventory system.


WORLD GEN:

World generation includes rivers (the light blue lines) and roads (the brown lines). The roads are the starting basis for a town generation system along with positioning dungeons on the world map. Each character represents a biome that can be chosen and visited. The biomes are generated using layered noise maps

Here are a few pictures showing variation in world map generation:

![world1](https://user-images.githubusercontent.com/92053987/186792186-0f7da930-6bec-462a-ba25-83f9cbee2985.PNG)

![world2](https://user-images.githubusercontent.com/92053987/186792204-e512c0b6-7dce-4c1b-9251-c1cb2f58a8c6.PNG)

![world3](https://user-images.githubusercontent.com/92053987/186792209-60960037-3733-445b-bc58-66e57a0b8301.PNG)





BIOMES:

Each character represents a biome that can be opened and visited. Each tile is procedurally generated and persistent.

![rocky](https://user-images.githubusercontent.com/92053987/186792231-b2f557db-343d-4ffa-8d79-b14fb575e89e.PNG)

![snowy](https://user-images.githubusercontent.com/92053987/186792245-5b393b71-ccf6-4930-8431-fa6ce691d04a.PNG)

![jungle+inventory](https://user-images.githubusercontent.com/92053987/186792257-37140808-4121-44bc-a80d-45a280391474.PNG)
