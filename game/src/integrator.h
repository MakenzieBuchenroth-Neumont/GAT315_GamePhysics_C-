#pragma once
#include "body.h"

inline void explicitEuler(nkBody* body, float timeStep) {
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timeStep));
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timeStep));
}

inline void semiImplicitEuler(nkBody* body, float timeStep) {
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timeStep));
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timeStep));
}