//---------------------------------------------------------------------
//---------------------------------------------------------------------
//  (c) David Dalström
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Game.h"
#include "A_Star.h"
#include "Terrain.h"
#include <iostream>
#include <cmath>

using namespace std;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Game::Game(void){
	mW = 1272.f, mH = 732.f;
	mMouseX = mMouseY = 0;
	mMouseButton = mMouseState = 0,
	mGlutGetModifiers = 0;
  	_started = false;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
Game::~Game(void){}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::ChangeSize(int w, int h){
	mW = w, mH = h;
	glViewport(0,0,mW,mH);                         // Reset Viewport
	glMatrixMode(GL_PROJECTION); glLoadIdentity(); // Reset The Projection Matrix
	glOrtho(0.0f,mW,mH,0.0f,-1.0f,1.0f);           // Create Ortho View (0,0 At Top Left)
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();  // Reset The Modelview Matrix
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::NormalKeys(unsigned char key, int x, int y){
	if (key >= '0' && key <= '9'){}
	if (key == 13){}
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::SpecialKeys(int key, int x, int y){
    if (key == GLUT_KEY_LEFT){}
    if (key == GLUT_KEY_RIGHT){}
    if (key == GLUT_KEY_UP){}
    if (key == GLUT_KEY_DOWN){}
    if (key == GLUT_KEY_F1){}
    if (key == GLUT_KEY_F2){}
    if (key == GLUT_KEY_F3){}
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Game::Mouse(int button, int state, int x, int y){
	mMouseButton = button;//GLUT_LEFT_BUTTON/GLUT_MIDDLE_BUTTON/GLUT_RIGHT_BUTTON
	mMouseState = state;//GLUT_DOWN/GLUT_UP
	mGlutGetModifiers = glutGetModifiers();
	mMouseX = x; mMouseY = y;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//A simple C-string based print function
void Game::Gfx_Text(float x, float y, const char *fmt, ...){
	char text[256]; va_list	ap;
	if (fmt == NULL) return;
	va_start(ap, fmt); vsprintf(text, fmt, ap); va_end(ap);
	glPushMatrix(); glLoadIdentity();
    glRasterPos2f(x,y);
    for (char *c=text; *c != '\0'; c++)
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
	glPopMatrix();
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------

Pathfinder::Pathfinder(unsigned int width, unsigned int height)
: Game()
{
	cout << "Pathfinder::Pathfinder(), width:height = " << width << ":" << height << endl;
  _found_path = false;
	int n = 0;
	// Create the game grid. The tiles of the grid are placed in the row vectors.
	_grid = shared_ptr<TileMap>(new TileMap());
	for (unsigned int row = 0; row < height; ++row) {
		shared_ptr<TileRow> row_vector(new TileRow());
		_grid->push_back(row_vector);
		for (unsigned int column = 0; column < width; ++column) {
			shared_ptr<Tile> t(new Tile());
			t->_coordinate.first = column;
			t->_coordinate.second = row;
      
      // Create random terrain for each tile with different frequency depending on type.
      // A wall surrounds the map so each border tile has the "wall" terrain type.
			if ((row == (height - 1)) || (row == 0) || (column == 0) || (column == (width - 1)))
				n = 10;
      else n = rand() % 10;
			switch (n) {
          // Grass terrain has the highest frequency (50%)
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				t->_terrain = grass;
				break;
			case 5:
				t->_terrain = water;
				break;
			case 6:
			case 7:
				t->_terrain = woods;
				break;
			case 10:
				t->_terrain = wall;
				break;
			default:
				t->_terrain = grass;
			};			
			row_vector->push_back(t);
		}
	}
	_a_star = new A_Star(_grid, Coordinate(1 + rand() % (width - 1), 1 + rand() % (height - 1)),
                               Coordinate(1 + rand() % (width - 1), 1 + rand() % (height - 1)));
}

void Pathfinder::set_tile(unsigned int x, unsigned int y, const Terrain& t)
{
	if ((x < 0) || 
			(x >= (*_grid)[0]->size()) ||
			(y < 0) ||
			(y >= _grid->size()))
		return;

	shared_ptr<TileRow> row = (*_grid)[y];
	(*row)[x]->_terrain = t;
}

Pathfinder::~Pathfinder()
{

}

void Pathfinder::update()
{
  if (_started)
    update_tiles();
}

void Pathfinder::update_tiles()
{
	if (!_found_path)
		_found_path = _a_star->find_path();
}

void Pathfinder::SpecialKeys(int key, int x, int y)
{
  if (key == GLUT_KEY_F1) { _started = true; }
  if (key == GLUT_KEY_F2) {}
  if (key == GLUT_KEY_F3) {}
  if (key == GLUT_KEY_F8) { reset_grid(); }
  if (key == GLUT_KEY_F10) { exit(1); }	
}

void Pathfinder::Mouse(int button, int state, int x, int y)
{
	mMouseButton = button;//GLUT_LEFT_BUTTON/GLUT_MIDDLE_BUTTON/GLUT_RIGHT_BUTTON
	mMouseState = state;//GLUT_DOWN/GLUT_UP
	mGlutGetModifiers = glutGetModifiers();
	mMouseX = x; mMouseY = y;
}

void Pathfinder::mouseMotion(int x, int y)
{
  unsigned int grid_x = (*_grid)[0]->size();
	unsigned int grid_y = _grid->size();
	float x_scale = 1272 / grid_x;
	float y_scale = 732 / grid_y;
  unsigned int x_coord = floor(x / x_scale);
  unsigned int y_coord = floor(y / y_scale);
  if ((x_coord < grid_x) && (y_coord < grid_y)) {
    shared_ptr<Tile> tile = get_tile(x_coord, y_coord);
    tile->set_terrain(wall);
  }
}

void Pathfinder::Draw()
{
	// Start by updating the grid.
	update();
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );

	draw_grid();
	draw_open_list();
	draw_closed_list();

  glColor3ub(0,255,0);
	Gfx_Text(mW - 1200, mH - 10, "Press Mouse to draw Wall!");
  glColor3ub(0,255,0);
	Gfx_Text(mW - 950, mH - 10, "Press F1 to Start!");
  glColor3ub(0,255,0);
	Gfx_Text(mW - 760, mH - 10, "Press F8 to Reset!");
	glColor3ub(255,153,51);
	Gfx_Text(mW - 550, mH - 10, "Closed Tiles");
	glColor3ub(255,51,255);
	Gfx_Text(mW - 400, mH - 10, "Open Tiles");
	glColor3ub(255,0,0);
	Gfx_Text(mW - 150, mH - 10, "Press F10 to Exit!");
  
  // Legend
  glColor3ub(100, 255, 0);   // Grass
  Gfx_Text(mW - 50, mH - 650, "Grass");
  glColor3ub(102, 178, 255); // Water
  Gfx_Text(mW - 50, mH - 600, "Water");
  glColor3ub(153, 76, 0);    // Wood
  Gfx_Text(mW - 50, mH - 550, "Wood");
  glColor3ub(64, 64, 64);    // Wall
  Gfx_Text(mW - 50, mH - 500, "Wall");
  glColor3ub(0, 0, 255);    // Start
  Gfx_Text(mW - 50, mH - 450, "Start");
  glColor3ub(255, 0, 0);    // Goal
  Gfx_Text(mW - 50, mH - 400, "Goal");

	glutSwapBuffers();
}

shared_ptr<Tile> Pathfinder::get_tile(unsigned int x, unsigned int y)
{
	if ((x < 0) || 
			(x >= (*_grid)[0]->size()) ||
			(y < 0) ||
			(y >= _grid->size()))
		return nullptr;
	else {
		shared_ptr<TileRow> row = (*_grid)[y];
		return (*row)[x];
	}
}

void Pathfinder::draw_grid()
{
	unsigned int grid_x = (*_grid)[0]->size();
	unsigned int grid_y = _grid->size();
	float x_scale = 1272 / grid_x;
	float y_scale = 732 / grid_y;
	unsigned int n = 0;

	TileMatrix::iterator row;
	for (row = _grid->begin(); row != _grid->end(); ++row) {
		TileRow::iterator tile_iter;
		for (tile_iter = (*row)->begin(); tile_iter != (*row)->end(); ++tile_iter) {
			shared_ptr<Tile> t = (*tile_iter);
			float x_offset = x_scale * (t->_coordinate.first + 0.5f);
			float y_offset = y_scale * (t->_coordinate.second + 0.5f);
			glColor4ub(t->_terrain._red, t->_terrain._green, t->_terrain._blue, t->_terrain._alpha);
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

void Pathfinder::draw_open_list()
{

}

void Pathfinder::draw_closed_list()
{

}

void Pathfinder::reset_grid()
{
	// Randomize the grid.
  unsigned int height = _grid->size();
  unsigned int width = (*_grid)[0]->size();
  int n = 0;
  int y = 0, x = 0;
	TileMatrix::iterator row;
	for (row = _grid->begin(); row != _grid->end(); ++row) {
		TileRow::iterator tile_iter;
		for (tile_iter = (*row)->begin(); tile_iter != (*row)->end(); ++tile_iter) {
      		shared_ptr<Tile> t = *tile_iter;
			t->reset();
			// Create random terrain for each tile with different frequency depending on type.
			// A wall surrounds the map so each border tile has the "wall" terrain type.
			if ((y == (height - 1)) || (y == 0) || (x == 0) || (x == (width - 1)))
				n = 10;
	     	else n = rand() % 10;
			switch (n) {
	        // Grass terrain has the highest frequency (50%)
	        case 0:
	        case 1:
	        case 2:
	        case 3:
	        case 4:
	          t->_terrain = grass;
	          break;
	        case 5:
	          t->_terrain = water;
	          break;
	        case 6:
	        case 7:
	          t->_terrain = woods;
	          break;
	        case 10:
	          t->_terrain = wall;
	          break;
	        default:
	          t->_terrain = grass;
			};
	      ++x;
	    }
    ++y;
	}
  
  _found_path = false;
  _started = false;
  delete _a_star;
  _a_star = new A_Star(_grid, Coordinate(1 + rand() % (width - 1), 1 + rand() % (height - 1)),
                       Coordinate(1 + rand() % (width - 1), 1 + rand() % (height - 1)));
}
