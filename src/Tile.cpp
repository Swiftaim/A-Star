#include "Tile.h"
#include "Terrain.h"
#include <list>
#include <cmath>
#include <cfloat>
#include <iostream>


using namespace std;

/*
 *	The implementation class of the interface class Tile.
 *  The motivation for this construction is to hide implementation details.
 */
class Tile::Tile_Impl {
public:
	Tile_Impl(Coordinate);
	~Tile_Impl();
	/*
	 * Below are attributes and methods used by the A* algorithm.
     */
	/// Updates the parent tile if it results in a better fitness value.
	void set_parent(shared_ptr<Tile> parent);
	/// Calculates the heuristic distance from this tile to the goal.
	float calculate_H(Coordinate goal);
	/// The fitness function.
	float get_F() const;
	/// Reset the tile to the default state.
	void reset();

	/// The parent tile according to the A* algorithm.
	shared_ptr<Tile> _parent;
	/// The movement cost from start to this tile.
	float _g;
	/// The heuristic of this tile with respect to the goal.
	float _h;
	/// Coordinates of the Tile on a TileMap.
	Coordinate _coordinate; 
	/// The organism/terrain type at this location.
	Terrain _terrain;
};

Tile::Tile_Impl::Tile_Impl(Coordinate coord) 
: _parent(0), _g(BIG_G), _h(0.0f), _coordinate(coord), _terrain(grass)
{

}

Tile::Tile_Impl::~Tile_Impl()
{

}

float Tile::Tile_Impl::get_F() const
{
	return (_g + _h); 
}

void Tile::Tile_Impl::set_parent(shared_ptr<Tile> parent)
{
	float cost = _terrain._cost * sqrt(float(pow(_coordinate.first - parent->_impl->_coordinate.first, 2) +
       pow(_coordinate.second - parent->_impl->_coordinate.second, 2)));
	if ((cost + parent->_impl->_g) < _g) {
 		_g = cost + parent->_impl->_g;
		_parent = parent;
	}
}

float Tile::Tile_Impl::calculate_H(Coordinate goal)
{
	float probable_cost = (5 * grass._cost + 2 * woods._cost + water._cost) / 8;
	_h = sqrt(pow(probable_cost * (_coordinate.first - goal.first), 2) +
						      pow(probable_cost * (_coordinate.second - goal.second), 2));
	return _h;
}

void Tile::Tile_Impl::reset() 
{ 
	_g = BIG_G; 
	_h = 0.0f; 
	_parent = nullptr; 
	_terrain = grass; 
}

Tile::Tile(Coordinate coord) : _impl(unique_ptr<Tile::Tile_Impl>(new Tile_Impl(coord))) {}
Tile::~Tile() {}

void Tile::set_terrain(const Terrain& t)
{
    float cost = (t._cost < 0?_impl->_terrain._cost:t._cost);
    _impl->_terrain = t;
    _impl->_terrain._cost = cost;
}

void Tile::set_g(const float& g)
{
	_impl->_g = g;
}

float Tile::calculate_H(Coordinate goal)
{
	return _impl->calculate_H(goal);
}

shared_ptr<Tile> Tile::get_parent() const
{
	return _impl->_parent;
}

const Coordinate& Tile::get_coordinate() const
{
	return _impl->_coordinate;
}

const Terrain& Tile::get_terrain() const
{
	return _impl->_terrain;
}

void Tile::set_parent(shared_ptr<Tile> parent)
{
	_impl->set_parent(parent);
}

float Tile::get_F() const
{
	return _impl->get_F();
}

void Tile::reset()
{
	_impl->reset();
}
