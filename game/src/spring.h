#pragma once

typedef struct nkSpring{
	struct nkBody* body1;
	struct nkBody* body2;

	float restLength;
	float k; // stiffness

	struct nkSpring* next;
	struct nkSpring* prev;

} nkSpring_t;

extern nkSpring_t* nkSprings;

nkSpring_t* createSpring(struct nkBody* body1, struct nkBody* body2, float restLength, float k);
void addSpring(nkSpring_t* spring);
void destroySpring(nkSpring_t* spring);
void destroyAllSprings();

void applySpringForce(nkSpring_t* springs);