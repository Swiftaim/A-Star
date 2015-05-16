//---------------------------------------------------------------------
//---------------------------------------------------------------------
#ifndef GAME_H
#define GAME_H
//---------------------------------------------------------------------

#include "Tile.h"
#include <GLUT/glut.h>
#include <vector>
#include <map>

using namespace std;

class A_Star;

//---------------------------------------------------------------------
class Game {
public:
    //-------------------------------------------------------
    Game(void);
    virtual ~Game(void);
    virtual void update() = 0;
    //-------------------------------------------------------
    void  ChangeSize(int w, int h);
    virtual void Draw() {}
    //-------------------------------------------------------
    virtual void  NormalKeys(unsigned char key, int x, int y);
    virtual void  SpecialKeys(int key, int x, int y);
    virtual void  Mouse(int button, int state, int x, int y);
    virtual void mouseMotion(int x, int y) {}
    //-------------------------------------------------------
    void  Gfx_Text(float x, float y, const char *fmt, ...);
    //-------------------------------------------------------
    float mW, mH;
    int mMouseX, mMouseY;
    int mMouseButton, mMouseState, mGlutGetModifiers;
protected:
    bool _started;
  
    //-------------------------------------------------------
};
//---------------------------------------------------------------------

/*
 * The Pathfinder class finds the optimal path from a start location to a
 * goal location by using the A* algorithm.
 */
class Pathfinder : public Game {
public:
    Pathfinder(unsigned int width, unsigned int height);
    ~Pathfinder();
    void update();
    void Draw();
    void SpecialKeys(int key, int x, int y);
    void Mouse(int button, int state, int x, int y);
    void mouseMotion(int x, int y);

private:
    shared_ptr<Tile> get_tile(unsigned int x, unsigned int y);
    void set_tile(unsigned int x, unsigned int y, const Terrain& t);
    void create_block(unsigned int x, unsigned int y);
    void update_tiles();
    void draw_grid();
    void draw_open_list();
    void draw_closed_list();
    void reset_grid();
    // The actual grid data.
    shared_ptr<TileMap> _grid;
    A_Star* _a_star;
    bool _found_path;
};

#endif
