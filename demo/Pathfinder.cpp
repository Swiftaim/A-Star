#include "Pathfinder.h"
#include "A_Star.h"
#include "Terrain.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

Pathfinder::Pathfinder(unsigned int width, unsigned int height)
: Game(width, height)
{
	_found_path = false;
	// Create the game grid. The tiles of the grid are placed in the row vectors.
	_grid = shared_ptr<TileMap>(new TileMap());	
	for (unsigned int row = 0; row < height; ++row) {
		shared_ptr<TileRow> row_vector(new TileRow());
		_grid->push_back(row_vector);
		for (unsigned int column = 0; column < width; ++column) {
			shared_ptr<Tile> t(new Tile(make_pair(column, row)));
			t->set_random_terrain(width, height, column, row);	
			row_vector->push_back(t);
		}
	}
	
	_a_star = new A_Star(_grid, get_valid_start_coordinate(), get_valid_goal_coordinate());
}

Pathfinder::~Pathfinder()
{

}

Coordinate Pathfinder::get_traversable_random_coordinate()
{
	unsigned int width = (*_grid)[0]->size();
	unsigned int height = _grid->size();
	Coordinate coord = make_pair(1 + rand() % (width - 1), 1 + rand() % (height - 1));
	while(get_tile(coord.first, coord.second)->get_terrain()._cost == wall._cost)
		coord = make_pair(1 + rand() % (width - 1), 1 + rand() % (height - 1));
	return coord;
}

Coordinate Pathfinder::get_valid_start_coordinate()
{
	return get_traversable_random_coordinate();
}

Coordinate Pathfinder::get_valid_goal_coordinate()
{
	return get_traversable_random_coordinate();
}



void Pathfinder::set_tile(unsigned int x, unsigned int y, const Terrain& t)
{
	if ((x >= (*_grid)[0]->size()) ||
		(y >= _grid->size()))
		return;

	shared_ptr<TileRow> row = (*_grid)[y];
	(*row)[x]->set_terrain(t);
}

void Pathfinder::update()
{
  if (_started)
    update_tiles();
}

// Update tiles by letting the A* algorithm run another iteration.
// Tiles only change state buy beeing modified by A*.
void Pathfinder::update_tiles()
{
	if (!_found_path)
		_found_path = _a_star->find_path();
}

// Map function keys to actions (if any).
void Pathfinder::special_keys(int key, int x, int y)
{
  if (key == GLUT_KEY_F1) { _started = true; }
  if (key == GLUT_KEY_F2) {}
  if (key == GLUT_KEY_F3) {}
  if (key == GLUT_KEY_F8) { reset_grid(); }
  if (key == GLUT_KEY_F10) { exit(1); }	
}

// Capture a mouse button event.
void Pathfinder::mouse(int button, int state, int x, int y)
{
	_mouse_button = button; //GLUT_LEFT_BUTTON/GLUT_MIDDLE_BUTTON/GLUT_RIGHT_BUTTON
	_mouse_state = state;   //GLUT_DOWN/GLUT_UP
	_glut_modifiers = glutGetModifiers();
	_mouse_x = x;
	_mouse_y = y;
}

// Capture mouse motion event
void Pathfinder::mouse_motion(int x, int y)
{
	unsigned int grid_x = (*_grid)[0]->size();
	unsigned int grid_y = _grid->size();
	float x_scale = _width / grid_x;
	float y_scale = _height / grid_y;
	unsigned int x_coord = floor(x / x_scale);
	unsigned int y_coord = floor(y / y_scale);
	if ((x_coord < grid_x) && (y_coord < grid_y)) {
		shared_ptr<Tile> tile = get_tile(x_coord, y_coord);
		tile->set_terrain(wall);
	}
}

void Pathfinder::draw()
{
	// Start by updating the grid/map.
	update();
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );

	// Draw the map tiles.
	draw_grid();

	glColor3ub(0,255,0);
	gfx_text(_width - 1200, _height - 10, "Press Mouse to draw Wall!");
	glColor3ub(0,255,0);
	gfx_text(_width - 950, _height - 10, "Press F1 to Start!");
	glColor3ub(0,255,0);
	gfx_text(_width - 760, _height - 10, "Press F8 to Reset!");
	glColor3ub(255,153,51);
	gfx_text(_width - 550, _height - 10, "Closed Tiles");
	glColor3ub(255,51,255);
	gfx_text(_width - 400, _height - 10, "Open Tiles");
	glColor3ub(255,0,0);
	gfx_text(_width - 150, _height - 10, "Press F10 to Exit!");

	// Legend
	glColor3ub(100, 255, 0);   // Grass
	gfx_text(_width - 50, _height - 650, "Grass");
	glColor3ub(102, 178, 255); // Water
	gfx_text(_width - 50, _height - 600, "Water");
	glColor3ub(153, 76, 0);    // Wood
	gfx_text(_width - 50, _height - 550, "Wood");
	glColor3ub(64, 64, 64);    // Wall
	gfx_text(_width - 50, _height - 500, "Wall");
	glColor3ub(0, 0, 255);    // Start
	gfx_text(_width - 50, _height - 450, "Start");
	glColor3ub(255, 0, 0);    // Goal
	gfx_text(_width - 50, _height - 400, "Goal");

	glutSwapBuffers();
}

// Return the Tile object at coordinates (x, y).
shared_ptr<Tile> Pathfinder::get_tile(unsigned int x, unsigned int y)
{
	if ((x >= (*_grid)[0]->size()) ||
		(y >= _grid->size()))
		return nullptr;
	else {
		shared_ptr<TileRow> row = (*_grid)[y];
		return (*row)[x];
	}
}

// Here is where the actual map is drawn based on the individual tiles terrain type.
void Pathfinder::draw_grid()
{
	unsigned int grid_x = (*_grid)[0]->size();
	unsigned int grid_y = _grid->size();
	float x_scale = (_width - 64) / grid_x;
	float y_scale = (_height - 32) / grid_y;
	unsigned int n = 0;

	TileMatrix::iterator row;
	for (row = _grid->begin(); row != _grid->end(); ++row) {
		TileRow::iterator tile_iter;
		for (tile_iter = (*row)->begin(); tile_iter != (*row)->end(); ++tile_iter) {
			shared_ptr<Tile> t = (*tile_iter);
			float x_offset = x_scale * (t->get_coordinate().first + 0.5f);
			float y_offset = y_scale * (t->get_coordinate().second + 0.5f);
			glColor4ub(t->get_terrain()._red, 
						t->get_terrain()._green, 
						t->get_terrain()._blue, 
						t->get_terrain()._alpha);
			glBegin(GL_POLYGON);
			glVertex3f(x_offset - x_scale / 2, y_offset - y_scale / 2, 0.0f); // Upper left
			glVertex3f(x_offset + x_scale / 2, y_offset - y_scale / 2, 0.0f); // Upper right
			glVertex3f(x_offset + x_scale / 2, y_offset + y_scale / 2, 0.0f); // Lower right
			glVertex3f(x_offset - x_scale / 2, y_offset + y_scale / 2, 0.0f); // Lower left
			glEnd();
      		++n;
		}
	}
}

// Reset the map to a default state with random terrain types.
void Pathfinder::reset_grid()
{
	// Randomize the grid.
	unsigned int height = _grid->size();
	unsigned int width = (*_grid)[0]->size();
	int x = 0, y = 0;
	TileMatrix::iterator row;
	for (row = _grid->begin(); row != _grid->end(); ++row) {
		TileRow::iterator tile_iter;
		for (tile_iter = (*row)->begin(); tile_iter != (*row)->end(); ++tile_iter) {
	  		shared_ptr<Tile> t = *tile_iter;
			t->set_random_terrain(width, height, x, y);
	      	++x;
	    }
		++y;
	}

	_found_path = false;
	_started = false;
	delete _a_star;
	_a_star = new A_Star(_grid, get_valid_start_coordinate(), get_valid_goal_coordinate());
}
