#include <math.h>
#include "model.h"
#include "callbacks.h"
#include "move.h"



void moveObjectForward(World* world) {
				if(world->object1.position.z < 1950 && UpZCollision(world)==1){
					world->object1.position.z = world->object1.position.z + 5;     //M F
				}
}

void moveObjectBackward(World* world) {
				if(world->object1.position.z > -1950 /*&& DownZCollision*/){
					world->object1.position.z = world->object1.position.z - 5;     //M L
				}
}

void moveObjectLeft(World* world) {
				if(world->object1.position.x < 1950 /*&& LeftXCollision*/){
					world->object1.position.x = world->object1.position.x + 5;      //Sz B
				}
}

void moveObjectRight(World* world) {
				if(world->object1.position.x > -1950 /*&& RightXCollision*/){
					world->object1.position.x = world->object1.position.x - 5;      //Sz J
					
				}
}