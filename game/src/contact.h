#pragma once
#include "raylib.h"

typedef struct nkContact
{
	struct nkBody* body1;
	struct nkBody* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct nkContact* next;
} nkContact_t;

void addContact(nkContact_t* contact, nkContact_t** contacts);
void destroyAllContacts(nkContact_t** contacts);
