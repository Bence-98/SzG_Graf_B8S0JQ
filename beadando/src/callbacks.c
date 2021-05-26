#include <math.h>
#include <stdbool.h>

#include "callbacks.h"
#include "init.h"
#include "draw.h"
#include "model.h"
#include "move.h"

int isHelpOn = 0;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

void display(void)
{
	double elapsed_time = calc_elapsed_time();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	update_camera_position(&camera, elapsed_time);
	draw_content(&world);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)WINDOW_WIDTH / (GLdouble)WINDOW_HEIGHT, 0.1, 20000.0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	set_view_point(&camera);

	if(isHelpOn)
	{
		GLfloat torchForHelp[] = { 0.8, 0.8, 0.8, 0.8};
		glLightfv(GL_LIGHT1, GL_AMBIENT, torchForHelp);

		glLoadIdentity();
		gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

		draw_help(world.helpTexture);

		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	}

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;


    set_clear_camera_pose(&camera);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		action.move_forward = TRUE;
		break;
	case 'i':
		action.moveObjectForward = TRUE;
		break;
	case 'j':
		action.moveObjectLeft = TRUE;
		break;
	case 'k':
		action.moveObjectBackward = TRUE;
		break;
	case 'l':
		action.moveObjectRight = TRUE;
		break;		
	case 's':
		action.move_backward = TRUE;
		break;
	case 'a':
		action.step_left = TRUE;
		break;
	case 'd':
		action.step_right = TRUE;
		break;
	case 'q':
		action.move_down = TRUE;
		break;
	case 'e':
		action.move_up = TRUE;
		break;
	case '+':
		action.increase_light = TRUE;
		break;
	case '-':
		action.decrease_light = TRUE;
		break;
	case 112:
        isHelpOn = TRUE;
	    break;
	case 27:
		exit(0);
	}

	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		action.move_forward = FALSE;
		break;
	case 'i':
		action.moveObjectForward = FALSE;
		break;
	case 'j':
		action.moveObjectLeft = FALSE;
		break;
	case 'k':
		action.moveObjectBackward = FALSE;
		break;
	case 'l':
		action.moveObjectRight = FALSE;
		break;	
	case 's':
		action.move_backward = FALSE;
		break;
	case 'a':
		action.step_left = FALSE;
		break;
	case 'd':
		action.step_right = FALSE;
		break;
	case 'q':
		action.move_down = FALSE;
		break;
	case 'e':
		action.move_up = FALSE;
		break;
	case '+':
		action.increase_light = FALSE;
		break;
	case '-':
		action.decrease_light = FALSE;
		break;
  /*  case 112:
        isHelpOn = FALSE;
        break;*/
	}

	glutPostRedisplay();
}

void specialFunc(int key, int x, int y) {
	switch (key)
	{
		case GLUT_KEY_F1:
			if(isHelpOn == 1)
			{
				isHelpOn=0;
			}
			else isHelpOn = 1;
	}
}

void mouse(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

void motion(int x, int y)
{
	double horizontal, vertical;

	horizontal = mouse_x - x;
	vertical = mouse_y - y;

	rotate_camera(&camera, horizontal, vertical);

	mouse_x = x;
	mouse_y = y;

	glutPostRedisplay();
}

void idle()
{
    glutPostRedisplay();
}

double calc_elapsed_time()
{
	static int last_frame_time = 0;
	int current_time;
	double elapsed_time;

	current_time = glutGet(GLUT_ELAPSED_TIME);
	elapsed_time = (double)(current_time - last_frame_time) / 1000.0;
	last_frame_time = current_time;


	return elapsed_time;
}

void update_camera_position(struct Camera* camera, double elapsed_time)
{
	float speed = 60;
	double distance;

	distance = elapsed_time * CAMERA_SPEED*speed;

	if (action.move_forward == TRUE) {
		move_camera_forward(camera, distance);
	}

	if (action.move_backward == TRUE) {
		move_camera_backward(camera, distance);
	}

	if (action.step_left == TRUE) {
		step_camera_left(camera, distance);
	}

	if (action.step_right == TRUE) {
		step_camera_right(camera, distance);
	}

	if (action.move_up == TRUE) {
		move_camera_up(camera, distance);
	}

	if (action.move_down == TRUE) {
		move_camera_down(camera, distance);
	}

	if (action.increase_light == TRUE) {
		if (light_ambient[0] < 1)
			light_ambient[0] = light_ambient[1] = light_ambient[2] += 0.01;
			glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	}

	if (action.decrease_light == TRUE) {
		if (light_ambient[0] > -0.60)
			light_ambient[0] = light_ambient[1] = light_ambient[2] -= 0.01;
			glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	}



	if (action.moveObjectForward == TRUE) {
		moveObjectForward(&world);
	}	
	
	if (action.moveObjectBackward == TRUE) {
		moveObjectBackward(&world);
	}	
	if (action.moveObjectRight == TRUE) {
		moveObjectRight(&world);
	}
	if (action.moveObjectLeft == TRUE) {
		moveObjectLeft(&world);
	}

	
}

int coords[4][38] = {
        {1600, 600, 1200, 800 , -375, -1600, -1225, -400, 25  , 400, -800, -1575, -1300, -1025, -1500, -775, -500, -225, -375, 800, 1600, 1325 , 1000, 1175, 1350, 675 , 1325 , 400  , 0 , -825, -1650, -1200, -600 , 0    , -200, -825, -550 , -275 },//Sz
        {1450, 600, 1125, 1175, 1600, 1425 , 1200 , 1375, 1200, 900, 900 , 750  , 600  , 300  , 0    , 300 , 0   , 200 , 400 , 200, -375, -1000, -575, -100, -375, -725, -1650, -1000, 0 , -200, -875 , -1100, -1625, -1100, -575, -875, -1225, -1000},//M
        {5   , 280, 5   , 5   , 240 , 5    , 80   , 5   , 80  , 5  , 160 , 5    , 60   , 5    , 100  , 5   , 60  , 5   , 35  , 155, 5   , 60   , 5   , 40  , 5   , 5   , 135  , 5    , 5 , 160 , 5    , 5    , 125  , 5    , 120 , 5   , 60   , 5    }, //Sz
        {110 , 5  , 100 , 80  , 5   , 40   , 5    , 40  , 5   , 55 , 5   , 25   , 5    , 55   , 5    , 55  , 5   , 35  , 5   , 5  , 120 , 5    , 90  , 5   , 50  , 180 , 5    , 200  , 45, 5   , 140  , 100  , 5    , 100  , 5   , 65  , 5    , 40   } //M
};

int CheckCollision(World* world) // AABB - AABB collision
{
    int hit = 1;
    for (int i = 0; i<38; i++) {


bool collisionX = world->object1.position.x + 50 >= coords[1][i] - coords[3][i]*5 &&
                    coords[1][i] + coords[3][i]*5 >= world->object1.position.x - 50;

bool collisionZ = world->object1.position.z + 50 >= coords[2][i] - coords[4][i]*5 &&
                    coords[2][i] + coords[4][i]*5 >= world->object1.position.z - 50;

if (collisionX==true && collisionZ==true)
    hit = 0;
        }
   // hit=1;
return hit;
}