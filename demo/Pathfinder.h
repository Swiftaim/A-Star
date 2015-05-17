/*
 *	Pathfinder is a simple simulation that allows the user to observe
 *  one of the most heavily used search algorithms (A*) in many games.
 */
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Game.h"
#include "Tile.h"
#include <vector>
#include <map>

class A_Star;

/*
 * The Pathfinder class finds the optimal path from a start location to a
 * goal location by using the A* algorithm.
 * It also creates the world map and draws the simple graphical representation
 * of that map in OpenGL.
 * The real educational value of this demo is how it plots the A* progression.
 */
class Pathfinder : public Game {
public:
	/// Constructs a random world map of size width * height.
    Pathfinder(unsigned int width, unsigned int height);
    ~Pathfinder();
    
    /// The draw() method simply draws the entire scene by using the OpenGL framework.
    /// The method is invoked by the OpenGL rendering engine for each cycle.
    void draw();
    void special_keys(int key, int x, int y);
    void mouse(int button, int state, int x, int y);
    void mouse_motion(int x, int y);

protected:
	/// The game rendering engine calls update before every rendering cycle of the game world.
    /// The update() method thus has to update the state of all entities subject to rendering.
    void update();

private:
    shared_ptr<Tile> get_tile(unsigned int x, unsigned int y);
    void set_tile(unsigned int x, unsigned int y, const Terrain& t);
    void create_block(unsigned int x, unsigned int y);
    void update_tiles();
    void draw_grid();
    void reset_grid();
    Coordinate get_traversable_random_coordinate();
    Coordinate get_valid_start_coordinate();
    Coordinate get_valid_goal_coordinate();
    // The actual grid data.
    shared_ptr<TileMap> _grid;
    A_Star* _a_star;
    bool _found_path;
};


#endif // PATHFINDER_H