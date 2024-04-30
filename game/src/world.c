#include "world.h"
#include <stdlib.h>
#include <assert.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* createBody(Vector2 mousePosition) {
	Body* newBody = (Body*)malloc(sizeof(Body));
	assert(newBody);

	newBody->position = mousePosition;
	newBody->velocity.x = 0;
	newBody->velocity.y = 0;
	newBody->force.x = 0;
	newBody->force.y = 0;

	newBody->prev = NULL;
	newBody->next = bodies;

	if (bodies != NULL) {
		bodies->prev = newBody;
	}

	bodies = newBody;

	bodyCount++;
	return newBody;
}

void destroyBody(Body* body) {
	assert(body != NULL);

	if (body->prev != NULL) {
		body->prev->next = body->next;
	}
	if (body->next != NULL) {
		body->next->prev = body->prev;
	}

	if (bodies == body) {
		bodies = body->next;
	}
	bodyCount--;
	free(body);
}