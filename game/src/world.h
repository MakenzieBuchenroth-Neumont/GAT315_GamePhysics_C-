#pragma once
#include "body.h"

extern nkBody* nkBodies;
extern int nkBodyCount;

nkBody* createBody(Vector2 mousePosition);
void destroyBody(nkBody* body);