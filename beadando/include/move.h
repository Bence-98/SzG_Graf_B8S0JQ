#ifndef INCLUDE_MOVE_H_
#define INCLUDE_MOVE_H_

#include "model.h"
#include <stdbool.h>



void moveObjectForward(World* world);
void moveObjectBackward(World* world);
void moveObjectRight(World* world);
void moveObjectLeft(World* world);
void moveObjectRandom(World* world);
int CheckCollision(World* world);


#endif /* INCLUDE_MOVE_H_ */
