#ifndef TILE_H
#define TILE_H

#include "Terrain.h"
#include <vector>
#include <cfloat>

using namespace std;

/// The coordinate of a Tile is of type Coordinate.
typedef pair<int, int> Coordinate;
/// The initial value of a Tiles path cost.
const float BIG_G = 1000000.0f;

/*
 * The map is represented by a grid of square tiles.
 * A tile consists of a location and terrain info.
 */ 
class Tile {
public:
  /// The implementation class of Tile.
  class Tile_Impl;
  /// The constructor puts the tile in a default state.
	Tile(Coordinate);
  ~Tile();
  /// Set the terrain type for this tile.
  void set_terrain(const Terrain& t);
  const Terrain& get_terrain() const;
  /// Set the g value for this tile.
  void set_g(const float& g);
  /// Calculates the heuristic distance from this tile to the goal.
  float calculate_H(Coordinate goal);
  /// Set the new parent tile.
  void set_parent(shared_ptr<Tile> parent);
  /// Get the parent tile.
  shared_ptr<Tile> get_parent() const;
  /// Get the coordinates fo the Tile.
  const Coordinate& get_coordinate() const;
  /// Get the fitness value for this Tile.
  float get_F() const;
  /// Reset the tile to the default state.
  void reset();
  /// Set a random terrain time.
  void set_random_terrain(unsigned int width, unsigned int height, int x, int y);

private:
  /// The implementation object.
  unique_ptr<Tile::Tile_Impl> _impl;

};

typedef vector<shared_ptr<Tile> > Path;
typedef vector<shared_ptr<Tile> > TileList;
typedef vector<shared_ptr<Tile> > TileRow;
typedef vector<shared_ptr<TileRow> > TileMatrix;
typedef TileMatrix TileMap;

#endif