#include <math.h>
#include "model.h"
#include "callbacks.h"
#include "move.h"



void moveObjectForward(World* world) {
				if(world->object1.position.z < 1930 ){
					world->object1.position.z = world->object1.position.z + 10;
				}
}

void moveObjectBackward(World* world) {
				if(world->object1.position.z > -1930 ){
					world->object1.position.z = world->object1.position.z - 10;
				}
}

void moveObjectLeft(World* world) {
				if(world->object1.position.x < 1930 ){
					world->object1.position.x = world->object1.position.x + 10;
				}
}

void moveObjectRight(World* world) {
				if(world->object1.position.x > -1930 ){
					world->object1.position.x = world->object1.position.x - 10;
					
				}
}

