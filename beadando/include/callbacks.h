#ifndef INCLUDE_CALLBACKS_H_
#define INCLUDE_CALLBACKS_H_

#include "camera.h"
#include "move.h"
#include <stdbool.h>

#include <GL/glut.h>

int mouse_x, mouse_y;

struct Camera camera;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

struct Action
{
	int move_forward;
	int move_backward;
	int step_left;
	int step_right;
	int move_up;
	int move_down;
	int increase_light;
	int decrease_light;

	int moveObjectForward;
	int moveObjectBackward;
	int moveObjectRight;
	int moveObjectLeft;


};
struct Action action;

/**
 * Objektum mozgatasa.
 */


void moveObjectForward(World* world);
void moveObjectBackward(World* world);
void moveObjectRight(World* world);
void moveObjectLeft(World* world);
void moveObjectRandom(World* world);
//bool CheckCollision(World* world);

/**
 * Set the callbacks for GLUT.
 */
void set_callbacks();

/**
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);


/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call after key on keyboard backed up.
 */
void keyboardUp(unsigned char key, int x, int y);

/**
 * Call when special key on keyboard is pressed.
 */
void specialFunc(int key, int x, int y);

/**
 * Call after mouse event.
 */
void mouse(int button, int state, int x, int y);

/**
 * Call when in motion
 */
void motion(int x, int y);

/**
 * Call when there is no other event.
 */
void idle();

/**
 * Returns the elapsed time since the program started.
 */
double calc_elapsed_time();

/**
 * Refreshes the position of the camera.
 */
void update_camera_position(struct Camera* camera, double elapsed_time);



#endif /* INCLUDE_CALLBACKS_H_ */
