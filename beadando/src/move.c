#include <math.h>
#include "model.h"
#include "callbacks.h"
#include "move.h"

/**
 * Move Object
 */

void moveObjectForward(World* world) {
				if(world->object1.position.z < 1950 && CheckCollision(world)){
					world->object1.position.z = world->object1.position.z + 10;     //M F
				}
				else{
                    world->object1.position.z = 1910;
                    world->object1.position.x = 1910;
				}
}

void moveObjectBackward(World* world) {
				if(world->object1.position.z > -1950 && CheckCollision(world)){
					world->object1.position.z = world->object1.position.z - 10;     //M L
				}
                else{
                    world->object1.position.z = 1910;
                    world->object1.position.x = 1910;
                }
}

void moveObjectLeft(World* world) {
				if(world->object1.position.x < 1950 && CheckCollision(world)){
					world->object1.position.x = world->object1.position.x + 10;      //Sz B
				}
                else{
                    world->object1.position.z = 1910;
                    world->object1.position.x = 1910;
                }
}

void moveObjectRight(World* world) {
				if(world->object1.position.x > -1950 && CheckCollision(world)){
					world->object1.position.x = world->object1.position.x - 10;      //Sz J
				}
                else{
                    world->object1.position.z = 1910;
                    world->object1.position.x = 1910;
                }
}