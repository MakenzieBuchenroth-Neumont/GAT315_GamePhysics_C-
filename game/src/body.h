#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum {
	BT_STATIC,
	BT_KINEMATIC,
	BT_DYNAMIC
} nkBody_t;

typedef enum {
	FM_FORCE,
	FM_IMPULSE,
	FM_VELOCITY
} nkForceMode_t;

typedef struct nkBody {
	nkBody_t type;

	// acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;

	// color - hsv

	float mass;
	float inverseMass; // 1 / mass (static = 0)
	float gravityScale;
	float damping;

	float restitution;

	Vector3 color;

	struct nkBody* next;
	struct nkBody* prev;
} nkBody;

inline void applyForce(nkBody* body, Vector2 force, nkForceMode_t forceMode) {
	if (body->type != BT_DYNAMIC) return;

	switch (forceMode) {
	case FM_FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case FM_IMPULSE:
		// applies a sudden change in momentum (velocity)
		body->velocity = Vector2Add(body->velocity, Vector2Scale(force, body->inverseMass));
		break;
	case FM_VELOCITY:
		body->velocity = force;
		break;
	}
}

inline void clearForce(nkBody* body) {
	body->force = Vector2Zero();
}

void step(nkBody* body, float timeStep);