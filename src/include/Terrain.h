#ifndef TERRAIN_H
#define TERRAIN_H

/*
 * Terrain is an attribute of a tile which tells how costly it is to traverse.
 * It also has a fatigue attribute which is multiplied for each tile in the path.
 * The fatigue may be used to emulate sand as being quite fast to traverse but at
 * a greater muscle strain.
 *
 * *** NOTE *** fatigue is not yet implemented!
 */
struct Terrain {
	float _cost;            // The cost of traversing this type of terrain.
	float _fatigue;         // The fatigue induced by traversing this terrain type.
	unsigned int _red;      // RGB color of this terrain type with alpha.
	unsigned int _green;
	unsigned int _blue;
	unsigned int _alpha;
	inline void operator=(const Terrain& t2);
};

// Predefined terrain types with movement cost and rendering color.
static Terrain grass = { 10.0f, 1.0f, 100, 255, 0, 255};
static Terrain water = { 1000.0f, 2.0f, 153, 255, 255, 255};
static Terrain woods = { 100.0f, 1.5f, 153, 76, 0, 255};
static Terrain wall = { 100000.0f, 100.0f, 64, 64, 64, 255};

// Special terrain types used to illustrate various states of the algorithm.
static Terrain a_star_open = { -1.0f, 1.0f, 255, 51, 255, 255};
static Terrain a_star_closed = { -1.0f, 1.0f, 255, 153, 51, 255};
static Terrain a_star_start = { -1.0f, 1.0f, 0, 0, 255, 255};
static Terrain a_star_goal = { -1.0f, 1.0f, 255, 0, 0, 255};

void Terrain::operator=(const Terrain& t2) 
{ 
	_cost = t2._cost;
	_fatigue = t2._fatigue;
	_red = t2._red;
	_green = t2._green;
	_blue = t2._blue;
	_alpha = t2._alpha;
}

#endif
