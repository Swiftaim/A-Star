#ifndef A_STAR_H
#define A_STAR_H

#include "Tile.h"
#include <memory>

using namespace std;

/*
 * Class A_Star is the interface of the A* algorithm.
 * Given a "map" and the coordinates of the start and goal positions, it will
 * find the optimal path with respect to the cost/speed of getting their.
 */
class A_Star {
public:
	A_Star(shared_ptr<TileMap> world_map, Coordinate start, Coordinate goal);
	~A_Star();
	/// Find a path from start to goal by using the A* algorithm.
	bool find_path();
	/// Get the resulting optimal path.
	const Path& get_path() const;

private:
	/// The implementation class of A_Star.
	class A_Star_Impl;
	/// The implementation object.
	unique_ptr<A_Star_Impl> _impl;
};

#endif
