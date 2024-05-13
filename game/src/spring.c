#include "spring.h"
#include "spring.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

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

//void destroyAllSprings() {
//}

void applySpringForce(nkSpring_t* springs) {

}