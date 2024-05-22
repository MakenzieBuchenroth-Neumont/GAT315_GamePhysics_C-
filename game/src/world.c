#include "world.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

nkBody* nkBodies = NULL;
int nkBodyCount = 0;
Vector2 nkGravity;

nkBody* createBody(Vector2 position, float mass, nkBody_t bodyType) {
	nkBody* body = (nkBody*)malloc(sizeof(nkBody));
	assert(body);

	memset(body, 0, sizeof(nkBody));
	body->position = position;
	body->mass = mass;
	body->inverseMass = (bodyType == BT_DYNAMIC) ? 1 / mass : 0;
	body->type = bodyType;

	return body;
}

void addBody(nkBody* body) {
	assert(body);

	body->prev = NULL;
	body->next = nkBodies;

	if (nkBodies != NULL) {
		nkBodies->prev = body;
	}

	nkBodies = body;

	nkBodyCount++;
	return body;
}

void destroyBody(nkBody* body) {
	assert(body != NULL);

	if (body->prev != NULL) {
		body->prev->next = body->next;
	}
	if (body->next != NULL) {
		body->next->prev = body->prev;
	}

	if (nkBodies == body) {
		nkBodies = body->next;
	}
	nkBodyCount--;
	free(body);
}

void destroyAllBodies() {
	if (!nkBodies) return;

	nkBody* body = nkBodies;
	while (body) {
		nkBody* next = body->next;
		free(body);
		body = next;
	}

	nkBodies = NULL;
}