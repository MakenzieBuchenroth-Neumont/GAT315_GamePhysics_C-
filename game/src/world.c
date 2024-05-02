#include "world.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

nkBody* nkBodies = NULL;
int nkBodyCount = 0;

nkBody* createBody(Vector2 mousePosition) {
	nkBody* body = (nkBody*)malloc(sizeof(nkBody));
	assert(body);

	memset(body, 0, sizeof(nkBody));

	body->position = mousePosition;

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