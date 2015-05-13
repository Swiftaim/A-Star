#include "A_Star.h"
#include <algorithm>
#include <iostream>
#include <memory>

using namespace std;

/*
 * A_Star_Impl is the implementation class for the A* algorithm.
 * The purpose of the "pimpl" idiom, in this case, is to hide implementation details
 * by providing a more "pure" encapsulation.
 */
class A_Star::A_Star_Impl {
public:
	A_Star_Impl(shared_ptr<TileMap> world_map, Coordinate start, Coordinate goal);
	~A_Star_Impl();
	/// Find the optimal path
	bool find_path();
	/// Get the resulting optimal path.
	const Path& get_path() const { return _the_path; }
	/// Move into the coordinate c and investigate its surroundings.
	void move_to(shared_ptr<Tile> tile);
	/// Get the best tile from the open list (lowest F cost).
	shared_ptr<Tile> get_best_tile();
	// Helper method to get the tile at a certain coordinate.
	shared_ptr<Tile> get_tile(const Coordinate c);
	/// Add to open list. Open tiles are candidates for the optimal path.
	bool add_to_open_list(shared_ptr<Tile> tile, shared_ptr<Tile> parent);
	/// Update neighbours, e.g. set parent tile for each neighbouring tile. 
	void update_neighbours(shared_ptr<Tile> parent);

	/// Various attributes needed by the algorithm.
	Coordinate _start;
	Coordinate _goal;
  	shared_ptr<Tile> _start_tile;
	shared_ptr<Tile> _goal_tile;
	TileList _open_list;
	TileList _closed_list;
	shared_ptr<TileMap> _map;
	Path _the_path;
};

A_Star::A_Star_Impl::A_Star_Impl(shared_ptr<TileMap> world_map, Coordinate start, Coordinate goal)
: _map(world_map), _start(start), _goal(goal)
{
	cout << "A_Star_Impl::A_Star_Impl(), start: [" << start.first << ", " << start.second << 
		"], goal: [" << goal.first << ", " << goal.second << "]" << endl;
	// Add the start location to the open list because 
	// that is where the algorithm will start from.
	_start_tile = get_tile(start);
 	_start_tile->_terrain = a_star_start;
	_start_tile->calculate_H(goal);
	_start_tile->_g = 0.0f;
	_open_list.push_back(_start_tile);
	// Get the goal tile for later use.
	_goal_tile = get_tile(goal);
  	_goal_tile->_terrain = a_star_goal;
	cout << "Start Tile _g=" << _start_tile->_g << ", _h=" << _start_tile->_h << ", F=" << _start_tile->get_F() << endl;
	//update_neighbours(start_tile);
	cout << "Open List content, F values: [ ";
	for (TileList::iterator iter = _open_list.begin(); iter != _open_list.end(); ++iter) {
		cout << (*iter)->get_F() << " ";
	}
	cout << "]" << endl;
}

A_Star::A_Star_Impl::~A_Star_Impl()
{
	
}

// Run one iteration then return status.
// The reason is to allow the program to render the map between iterations.
bool A_Star::A_Star_Impl::find_path()
{
	// The flag will be set to true when the
	// goal tile is found.
	bool goal_found = false;

	shared_ptr<Tile> tile = get_best_tile();
	if (!tile)
		return false;
	if (tile == _goal_tile) {
		goal_found = true;
		while (tile->_parent != nullptr) {
		  tile->_terrain = a_star_goal;
		  _the_path.push_back(tile);
		  tile = tile->_parent;
		}
	}
	else update_neighbours(tile);

	// Make sure atsrt/stop has the correct terrain type otherwise they will not be visible.
	_start_tile->set_terrain(a_star_start);
	_goal_tile->set_terrain(a_star_goal);
	return goal_found;
}

// Each tile has up to 8 neighbours. Add them to the open list if they have not been there before.
void A_Star::A_Star_Impl::update_neighbours(shared_ptr<Tile> parent)
{
	Coordinate p_loc = parent->_coordinate;
	shared_ptr<Tile> t = get_tile(Coordinate(p_loc.first, p_loc.second - 1)); // Up
	add_to_open_list(t, parent);
	t = get_tile(Coordinate(p_loc.first + 1, p_loc.second - 1)); // Up-Right
	add_to_open_list(t, parent);
	t = get_tile(Coordinate(p_loc.first + 1, p_loc.second)); // Right
	add_to_open_list(t, parent);
	t = get_tile(Coordinate(p_loc.first + 1, p_loc.second + 1)); // Down-Right
	add_to_open_list(t, parent);
	t = get_tile(Coordinate(p_loc.first, p_loc.second + 1)); // Down
	add_to_open_list(t, parent);
	t = get_tile(Coordinate(p_loc.first - 1, p_loc.second + 1)); // Down-Left
	add_to_open_list(t, parent);
	t = get_tile(Coordinate(p_loc.first - 1, p_loc.second)); // Left
	add_to_open_list(t, parent);
	t = get_tile(Coordinate(p_loc.first - 1, p_loc.second - 1)); // Up-Left
	add_to_open_list(t, parent);
}

// Add a tile to the open list if it hasn't been there before.
// The method will also set the parent tile.
bool A_Star::A_Star_Impl::add_to_open_list(shared_ptr<Tile> tile, shared_ptr<Tile> parent)
{
	if (!tile)
		return false;
	// Only tiles that are not occupied by walls are allowed to enter the open list.
	if ((tile->_terrain._cost < wall._cost) &&
      (find(_open_list.begin(), _open_list.end(), tile) == _open_list.end()) &&
			(find(_closed_list.begin(), _closed_list.end(), tile) == _closed_list.end())) {
		_open_list.push_back(tile);
		tile->calculate_H(_goal);
		tile->set_parent(parent);
    tile->set_terrain(a_star_open);
		return true;
	}
	else if (find(_open_list.begin(), _open_list.end(), tile) != _open_list.end())
		tile->set_parent(parent);
	return false;
}

// Get the tile with the lowest F value (the cost to move to that tile plus the distance to the goal tile).
shared_ptr<Tile> A_Star::A_Star_Impl::get_best_tile()
{
	if (_open_list.empty())
		return nullptr;

  shared_ptr<Tile> best = nullptr;
  float best_F = BIG_G;
  TileList::iterator iter;
  for (iter = _open_list.begin(); iter != _open_list.end(); ++iter) {
    if ((*iter)->get_F() < best_F) {
      best_F = (*iter)->get_F();
      best = *iter;
    }
  }
  
	_open_list.erase(find(_open_list.begin(), _open_list.end(), best));
	_closed_list.push_back(best);
	best->set_terrain(a_star_closed);
	return best;
}

shared_ptr<Tile> A_Star::A_Star_Impl::get_tile(const Coordinate c)
{
	if (c.second >= _map->size())
		return nullptr;
	shared_ptr<TileRow> row = (*_map)[c.second];
	if (c.first >= row->size())
		return nullptr;
	return (*row)[c.first];
}

A_Star::A_Star(shared_ptr<TileMap> world_map, Coordinate start, Coordinate goal)
: _impl(unique_ptr<A_Star_Impl>(new A_Star::A_Star_Impl(world_map, start, goal)))
{
	
}

A_Star::~A_Star() 
{
}

// Run one iteration then return status.
// The reason is to allow the program to render the map between iterations.
bool A_Star::find_path()
{
	return _impl->find_path();
}

const Path& A_Star::get_path() const 
{ 
	return _impl->get_path();
}
