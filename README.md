This is a simple demo of the A* algorithm. For a detailed description of the algorithm please head over to http://en.wikipedia.org/wiki/A*_search_algorithm.

Provides a library named libastar.so that implements the A* algorithm.

A demo application is provided that utilizes the libastar.so library.

Build
======
From the command line (OSX), just run "make".

Start the application with the command "cd demo && ./astar"

USER QUICK GUIDE
================
There is a fairly easy-to-use GUI which allows the following operations:

1) The application will start up with a random map generated for you.
2) On the right side of the window there is brief legend telling what the various colors represent in terms of terrain types.
3) At the bottom of the window the various usable keyboard keys are described (Start simulation, reset/new map, and exit application).
3.1) There is also a brief legend here describing the color of the open and closed tiles sets respectively.
4) Before starting the simulation with F1, draw some walls on the map to make it more interesting. Just press a mouse button and move the mouse. But beware, the algorithm will cut corners so don't leave any diagonal openings in your wall...
