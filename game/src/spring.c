#include "spring.h"
#include "mathf.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "body.h"

nkSpring_t* nkSprings = NULL;

nkSpring_t* createSpring(struct nkBody* body1, struct nkBody* body2, float restLength, float k) {
	nkSpring_t* spring = (nkSpring_t*)malloc(sizeof(nkSpring_t));
	assert(spring);

	memset(spring, 0, sizeof(nkSpring_t));

	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->k = k;

	return spring;
}

void addSpring(nkSpring_t* spring) {
	assert(spring);

	spring->prev = NULL;
	spring->next = nkSprings;

	if (nkSprings != NULL) {
		nkSprings->prev = spring;
	}

	nkSprings = spring;

	return spring;
}

void destroySpring(nkSpring_t* spring) {
	assert(spring != NULL);

	if (spring->prev != NULL) {
		spring->prev->next = spring->next;
	}
	if (spring->next != NULL) {
		spring->next->prev = spring->prev;
	}

	if (nkSprings == spring) {
		nkSprings = spring->next;
	}
	free(spring);
}

void destroyAllSprings() {
	if (!nkSprings) return;

	nkSpring_t* spring = nkSprings;
	while (spring) {
		nkSpring_t* next = spring->next;
		free(spring);
		spring = next;
	}

	nkSprings = NULL;
}

void applySpringForce(nkSpring_t* springs) {
	for (nkSpring_t* spring = springs; spring; spring = spring->next) {
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position); //<get direction vector from body2 to body1>
		if (direction.x == 0 && direction.y == 0) continue;
		
		float length = Vector2Length(direction); //<get length from direction>
		float x = length - spring->restLength;//<compute displacement from current length to resting length>;
		float force = -(spring->k * x); //<(f = -kx) compute force using product of displacement and stiffness(k)>;

		Vector2 ndirection = Vector2Normalize(direction); //<get direction normal>

		applyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		applyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}
}

void ApplySpringForcePosition(Vector2 position, nkBody* body, float restLength, float k, float damping) {
	// Check if the body pointer is null; if so, exit the function
	if (!body) return;

	// Calculate the direction vector from the body's position to the given position
	Vector2 direction = Vector2Subtract(position, body->position);

	// If the direction vector is zero (i.e., positions are the same), exit the function
	if (direction.x == 0 && direction.y == 0) return;

	// Calculate the length of the direction vector (distance between the two positions)
	float length = Vector2Length(direction);

	// Calculate the displacement from the rest length
	float x = length - restLength;

	// Apply Hooke's Law (f = -kx) to determine the spring force
	float force = (-k * x);

	// Normalize the direction vector
	Vector2 ndirection = Vector2Normalize(direction);

	// Calculate the damping force (opposing force due to velocity)
	float dampingForce = damping * Vector2DotProduct(body->velocity, ndirection);

	// Calculate the total force by combining spring force and damping force
	float totalForce = force + dampingForce;

	// Apply the total force to the body in the direction of the normalized vector
	applyForce(body, Vector2Scale(ndirection, -totalForce), FM_FORCE);
}