#ifndef TILE_H
#define TILE_H

#include "Terrain.h"
#include <vector>
#include <list>
#include <cmath>
#include <cfloat>

using namespace std;

const float BIG_G = FLT_MAX;

typedef pair<int, int> Coordinate;
/*
 * The map is represented by a grid of square tiles.
 * A tile consists of a location and terrain info.
 */ 
class Tile {
public:
  /// The constructor puts the tile in a default state.
	Tile();
  /// Coordinates of the Tile on a TileMap.
  Coordinate _coordinate; 
  /// The organism/terrain type at this location.
  Terrain _terrain;

  /*
   * Below are attributes and methods used by the A* algorithm.
   */
  /// The parent tile according to the A* algorithm.
  shared_ptr<Tile> _parent;
  /// The movement cost from start to this tile.
  float _g;
  /// The heuristic of this tile with respect to the goal.
  float _h;		
  float get_F() const;
  void set_parent(shared_ptr<Tile> parent);
  float calculate_H(Coordinate goal);
  void set_terrain(const Terrain& t) {
    float cost = (t._cost < 0?_terrain._cost:t._cost);
    _terrain = t;
    _terrain._cost = cost;
  }
  /// Reset the tile to the default state.
  void reset();
  friend bool operator<(const Tile& t1, const Tile& t2);
  friend ostream& operator<<(ostream& o, const Tile& t);
};

typedef vector<shared_ptr<Tile> > Path;
typedef vector<shared_ptr<Tile> > TileList;
typedef vector<shared_ptr<Tile> > TileRow;
typedef vector<shared_ptr<TileRow> > TileMatrix;
typedef TileMatrix TileMap;

#endif