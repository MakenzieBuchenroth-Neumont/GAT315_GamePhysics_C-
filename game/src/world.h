#pragma once
#include "raylib.h"
#include "body.h"

// forward declaration
typedef struct nkBody nkBody;

extern nkBody* nkBodies;
extern int nkBodyCount;
extern Vector2 nkGravity;

nkBody* createBody(Vector2 position, float mass, nkBodyType bodyType);
void addBody(nkBody* body);
void destroyBody(nkBody* body);