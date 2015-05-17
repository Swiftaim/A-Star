//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Pathfinder.h"
#include <cmath>
//---------------------------------------------------------------------

const unsigned int TILE_COLUMNS = 200;
const unsigned int TILE_ROWS = 100;

Pathfinder game(TILE_COLUMNS, TILE_ROWS);
// Map the rendering engine callback functions into game overloaded
// functions for custom behaviour.
void display() { game.draw(); }
void idle() { game.draw(); }
void normal_keys(unsigned char key, int x, int y) { game.normal_keys(key, x, y); }
void special_keys(int key, int x, int y) { game.special_keys(key, x, y); }
void mouse(int button, int state, int x, int y){ game.mouse(button, state, x, y); }
void mouse_motion(int x, int y) { game.mouse_motion(x, y); }
void change_size(int w, int h) { game.change_size(w, h); }
//---------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
    
	//----------------------Window
	glutInitWindowPosition(0,0);
	glutInitWindowSize(8 * TILE_COLUMNS, 8 * TILE_ROWS);
	glutCreateWindow("A* Simulation");
	glutReshapeFunc(change_size);
    
	//----------------------Draw
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1);
    
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
    
	glutKeyboardFunc(normal_keys);
	glutSpecialFunc(special_keys);
	glutMouseFunc(mouse);
  	glutMotionFunc(mouse_motion);
	//----------------------Main
	glutMainLoop();
    return 0;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
