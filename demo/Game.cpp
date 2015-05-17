#include "Game.h"
#include <cstdarg>
#include <cstdio>

Game::Game(float width, float height)
: _width(width), _height(height)
{
	_mouse_x = _mouse_y = 0;
	_mouse_button = _mouse_state = 0,
	_glut_modifiers = 0;
  	_started = false;
}

Game::~Game()
{

}

// The window size changes.
// Some OpenGL stuff going on here.
void Game::change_size(int w, int h)
{
	_width = w, _height = h;
	// Reset Viewport
	glViewport(0, 0, _width, _height);
	// Reset The Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	// Create Ortho View (0,0 At Top Left)
	glOrtho(0.0f, _width, _height, 0.0f, -1.0f, 1.0f);
	// Reset The Modelview Matrix
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

// All normal keystrokes are disabled by default.
void Game::normal_keys(unsigned char key, int x, int y){
	if (key >= '0' && key <= '9') {}
	if (key == 13) {}
}

// Most special keys are disabled by default.
void Game::special_keys(int key, int x, int y){
    if (key == GLUT_KEY_LEFT){}
    if (key == GLUT_KEY_RIGHT){}
    if (key == GLUT_KEY_UP){}
    if (key == GLUT_KEY_DOWN){}
    if (key == GLUT_KEY_F1){}
    if (key == GLUT_KEY_F2){}
    if (key == GLUT_KEY_F3){}
}

void Game::mouse(int button, int state, int x, int y)
{
	// GLUT_LEFT_BUTTON/GLUT_MIDDLE_BUTTON/GLUT_RIGHT_BUTTON
	_mouse_button = button;
	// GLUT_DOWN/GLUT_UP
	_mouse_state = state;
	_glut_modifiers = glutGetModifiers();
	// Position
	_mouse_x = x; _mouse_y = y;
}

// A simple C-string based print function
void Game::gfx_text(float x, float y, const char *fmt, ...){
	char text[256]; va_list	ap;
	if (fmt == 0) return;
	va_start(ap, fmt); vsprintf(text, fmt, ap); va_end(ap);
	glPushMatrix(); glLoadIdentity();
    glRasterPos2f(x,y);
    for (char *c=text; *c != '\0'; c++)
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
	glPopMatrix();
}
