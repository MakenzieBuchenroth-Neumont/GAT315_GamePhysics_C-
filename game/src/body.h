#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum {
	STATIC,
	KINEMATIC,
	DYNAMIC
} nkBodyType;

typedef struct nkBody {
	nkBodyType body;

	// force -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 force;

	float mass;
	float inverseMass; // 1 / mass (static = 0)

	struct nkBody* next;
	struct nkBody* prev;
} nkBody;

inline void applyForce(nkBody* body, Vector2 force) {
	body->force = Vector2Add(body->force, force);
}

inline void clearForce(nkBody* body) {
	body->force = Vector2Zero();
}