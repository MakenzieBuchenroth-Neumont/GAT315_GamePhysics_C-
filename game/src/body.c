#include "body.h"
#include "world.h"
#include "integrator.h"

void step(nkBody* body, float timeStep) {
	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(nkGravity, body->gravityScale), body->mass));
	body->acceleration = Vector2Scale(body->force, body->inverseMass);

	semiImplicitEuler(body, timeStep);

	// apply damping
	float damping = 1 / (1 + (body->damping * timeStep));
	body->velocity = Vector2Scale(body->velocity, damping);

	clearForce(body);
}