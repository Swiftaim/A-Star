/*
 * The code may be used freely as is.
 * Feel free to send comments or requests to david.dalstrom@gmail.com
 *
 * The Game code provides a simple framework for user interaction with
 * a game or other application that require user interaction.
 */

#ifndef GAME_H
#define GAME_H

#include <GLUT/glut.h>

/*
 * The Game class provides some common features such as keyboard interaction
 * and mouse actions for a large category of games.
 */
class Game {
public:
    // Initialize the game with a window size of width * height.
    Game(float width, float height);
    virtual ~Game(void);
    /// Must be overloaded by a concrete subclass.
    virtual void update() = 0;
    /// Handle the window "on change size" event.
    void  change_size(int w, int h);
    /// Nothing will obviously be drawn unless overloaded.
    virtual void draw() {}
    /// Handle keystroke events.
    virtual void normal_keys(unsigned char key, int x, int y);
    virtual void special_keys(int key, int x, int y);
    /// Handle mouse events.
    virtual void mouse(int button, int state, int x, int y);
    virtual void mouse_motion(int x, int y) {}
    /// Draw the specified text at the x, y location.
    void gfx_text(float x, float y, const char *fmt, ...);

protected:
    float _width, _height;
    int _mouse_x, _mouse_y;
    int _mouse_button, _mouse_state, _glut_modifiers;
    bool _started;
};

#endif
