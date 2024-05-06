#pragma once
#include "raylib.h"

// forward declaration
typedef struct nkBody nkBody;

extern nkBody* nkBodies;
extern int nkBodyCount;
extern Vector2 nkGravity;

nkBody* createBody(Vector2 mousePosition);
void destroyBody(nkBody* body);