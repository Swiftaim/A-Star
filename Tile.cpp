#include "Tile.h"
#include "Terrain.h"
#include <iostream>

using namespace std;

bool operator<(const Tile& t1, const Tile& t2) 
{ 
	return (t1.get_F() < t2.get_F());
}

ostream& operator<<(ostream& o, const Tile& t)
{
  return (o << t.get_F());
}

Tile::Tile() : _g(BIG_G), _h(0.0f), _parent(0), _terrain(grass) {}

float Tile::get_F() const
{
	return (_g + _h); 
}

void Tile::set_parent(shared_ptr<Tile> parent)
{
	float cost = _terrain._cost * sqrt(float(pow(_coordinate.first - parent->_coordinate.first, 2) +
																		       pow(_coordinate.second - parent->_coordinate.second, 2)));
//  cout << "Tile::set_parent(), parent->_g=" << parent->_g << ", cost=" << cost << ", _g=" << _g << ", _h=" << _h << endl;
	if ((cost + parent->_g) < _g) {
 		_g = cost + parent->_g;
		_parent = parent;
	}
//  cout << "Tile::set_parent(), parent->_g=" << parent->_g << ", cost=" << cost << ", _g=" << _g << ", _h=" << _h << endl;
}

float Tile::calculate_H(Coordinate goal)
{
	float average_cost = (5 * grass._cost + 2 * woods._cost + water._cost) / 8;
	float ideal_cost = grass._cost;
	float probable_cost = (5 * grass._cost + 2 * woods._cost) / 7;
	_h = sqrt(pow(probable_cost * (_coordinate.first - goal.first), 2) +
						      pow(probable_cost * (_coordinate.second - goal.second), 2));
  return _h;
}

void Tile::reset() 
{ 
	_g = BIG_G; 
	_h = 0.0f; 
	_parent = nullptr; 
	_terrain = grass; 
}
