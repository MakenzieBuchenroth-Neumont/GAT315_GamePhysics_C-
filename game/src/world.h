#pragma once
#include "body.h"

extern Body* bodies;
extern int bodyCount;

Body* createBody();
void destroyBody(Body* body);