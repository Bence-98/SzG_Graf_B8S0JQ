#include "GL/glut.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "draw.h"
#include "model.h"
#include "callbacks.h"

double roomSize = 2000;

GLfloat material_ambient_default[] = {0.9, 0.9, 0.9, 0.5};

void draw_teapot_for_light(){
    glPushMatrix();
        glTranslatef(120, 15, 120);
        glScalef(12, 12, 12);
        glutSolidTeapot(1.0);
    glPopMatrix();
}

void draw_content(World* world)
{
	Room roomToDraw = world -> room;
	glEnable(GL_TEXTURE_2D);

    glPushMatrix();
		draw_walls(roomToDraw);
		draw_ground(roomToDraw);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(world->object1.position.x, world->object1.position.y, world->object1.position.z);

		glMaterialfv(GL_FRONT, GL_AMBIENT, world->object1.material_ambient);


		glBindTexture(GL_TEXTURE_2D, world->object1.texture);
		glScalef(50.0f, 50.0f, 50.0f);

		draw_model(&world->object1.model);
    glPopMatrix();

    //bricks
    int coords[4][38] = {
            {1600, 600, 1200, 800 , -375, -1600, -1225, -400, 25  , 400, -800, -1575, -1300, -1025, -1500, -775, -500, -225, -375, 800, 1600, 1325 , 1000, 1175, 1350, 675 , 1325 , 400  , 0 , -825, -1650, -1200, -600 , 0    , -200, -825, -550 , -275 },//Sz
            {1450, 600, 1125, 1175, 1600, 1425 , 1200 , 1375, 1200, 900, 900 , 750  , 600  , 300  , 0    , 300 , 0   , 200 , 400 , 200, -375, -1000, -575, -100, -375, -725, -1650, -1000, 0 , -200, -875 , -1100, -1625, -1100, -575, -875, -1225, -1000},//M
            {5   , 280, 5   , 5   , 240 , 5    , 80   , 5   , 80  , 5  , 160 , 5    , 60   , 5    , 100  , 5   , 60  , 5   , 35  , 155, 5   , 60   , 5   , 40  , 5   , 5   , 135  , 5    , 5 , 160 , 5    , 5    , 125  , 5    , 120 , 5   , 60   , 5    }, //Sz
            {110 , 5  , 100 , 80  , 5   , 40   , 5    , 40  , 5   , 55 , 5   , 25   , 5    , 55   , 5    , 55  , 5   , 35  , 5   , 5  , 120 , 5    , 90  , 5   , 50  , 180 , 5    , 200  , 45, 5   , 140  , 100  , 5    , 100  , 5   , 65  , 5    , 40   } //M
    };
    for (int i = 0; i<38; i++) {
    glPushMatrix();
    glTranslatef(coords[0][i], 0, coords[1][i]);

    glMaterialfv(GL_FRONT, GL_AMBIENT, world->object2.material_ambient);


    glBindTexture(GL_TEXTURE_2D, world->object2.texture);
    glScalef(coords[2][i], 20, coords[3][i]);

    draw_model(&world->object2.model);
    glPopMatrix();
        }





    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient_default);
}

void draw_ground(Room room) {
	glBindTexture(GL_TEXTURE_2D, room.ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	for (x = -roomSize; x < roomSize; x += 50) {
		for (z = -roomSize; z < roomSize; z += 50) {
			glTexCoord2f(0.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}
void draw_walls(Room room) {
	glBindTexture(GL_TEXTURE_2D, room.left);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-roomSize, 0, -roomSize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-roomSize, roomSize, -roomSize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-roomSize, roomSize, roomSize);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-roomSize, 0, roomSize);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, room.right);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(roomSize, 0, roomSize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(roomSize, roomSize, roomSize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(roomSize, roomSize, -roomSize);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(roomSize, 0, -roomSize);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, room.front);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-roomSize, 0, -roomSize);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(roomSize, 0, -roomSize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(roomSize, roomSize, -roomSize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-roomSize, roomSize, -roomSize);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, room.back);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-roomSize, 0, roomSize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-roomSize, roomSize, roomSize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(roomSize, roomSize, roomSize);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(roomSize, 0, roomSize);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, room.top);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(roomSize, roomSize, roomSize);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(roomSize, roomSize, -roomSize);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-roomSize, roomSize, -roomSize);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-roomSize, roomSize, roomSize);
	glEnd();
}

void draw_triangles(const struct Model* model)
{
	int i, k;
	int vertex_index, texture_index, normal_index;
	double x, y, z, normal_x, normal_y, normal_z, u, v;

	glBegin(GL_TRIANGLES);

	for (i = 0; i < model->n_triangles; ++i) {
		for (k = 0; k < 3; ++k) {
			normal_index = model->triangles[i].points[k].normal_index;
			normal_x = model->normals[normal_index].x;
			normal_y = model->normals[normal_index].y;
			normal_z = model->normals[normal_index].z;
			glNormal3d(normal_x, normal_y, normal_z);

			vertex_index = model->triangles[i].points[k].vertex_index;
			x = model->vertices[vertex_index].x;
			y = model->vertices[vertex_index].y;
			z = model->vertices[vertex_index].z;
            switch(k){
            case 0:
                glTexCoord2f(0, 0);
                break;
            case 1:
                glTexCoord2f(0.1*z, 0);
                break;
            case 2:
                glTexCoord2f(0, 0.01);
                break;
            }
			glVertex3d(x, y, z);

		}
	}

	glEnd();
}


void draw_quads(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index, normal_index;
    double x, y, z, u, v;

	glBegin(GL_QUADS);

    for (i = 0; i < model->n_quads; ++i) {
        for (k = 0; k < 4; ++k) {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            // NOTE: The 1-v is model file specific!
            glTexCoord2f(u, 1-v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}

void draw_normals(const struct Model* model, double length)
{
	int i;
	double x1, y1, z1, x2, y2, z2;

	glColor3f(0, 0, 1);

	glBegin(GL_LINES);

	for (i = 0; i < model->n_vertices; ++i) {
		x1 = model->vertices[i].x;
		y1 = model->vertices[i].y;
		z1 = model->vertices[i].z;
		x2 = x1 + model->normals[i].x * length;
		y2 = y1 + model->normals[i].y * length;
		z2 = z1 + model->normals[i].z * length;
		glVertex3d(x1, y1, z1);
		glVertex3d(x2, y2, z2);
	}
	glEnd();
}

void draw_model(const struct Model* model)
{
	draw_triangles(model);
	draw_quads(model);
}

void draw_help(int texture) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}