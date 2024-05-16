#include "collision.h"
#include "contact.h"
#include "body.h"
#include "mathf.h"
#include <raymath.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

bool intersects(nkBody* body1, nkBody* body2) {
	// if distance <= radius
	float distance = Vector2Distance(body1->position, body2->position);
	float radius = body1->mass + body2->mass;

	return (distance <= radius);
}

void createContacts(nkBody* bodies, nkContact_t** contacts) {
	for (nkBody* body1 = bodies; body1; body1 = body1->next) {
		for (nkBody* body2 = body1->next; body2; body2 = body2->next) {
			if (body1 == body2) continue;
			if (body1->type != BT_DYNAMIC && body2->type != BT_DYNAMIC) continue;

			if (intersects(body1, body2)) {
				nkContact_t* contact = generateContact(body1, body2);
				addContact(contact, contacts);
			}
		}
	}
}

nkContact_t* generateContact(nkBody* body1, nkBody* body2) {
	nkContact_t* contact = (nkContact_t*)malloc(sizeof(nkContact_t));
	assert(contact);

	memset(contact, 0, sizeof(nkContact_t));

	contact->body1 = body1;
	contact->body2 = body2;

	Vector2 direction = Vector2Subtract(body1->position, body2->position);
	float distance = Vector2Length(direction);
	if (distance == 0)
	{
		direction = (Vector2){ getRandomFloatValue(-0.05f, 0.05f), getRandomFloatValue(-0.05f, 0.05f) };
	}

	float radius = (body1->mass + body2->mass);

	contact->depth = radius - distance;
	contact->normal = Vector2Normalize(direction);
	contact->restitution = (body1->restitution + body2->restitution) * 0.5f;

	return contact;
}


void separateContacts(nkContact_t* contacts) {
	for (nkContact_t* contact = contacts; contact; contact = contact->next) {
		float totalInverseMass = (contact->body1->inverseMass + contact->body2->inverseMass);
		Vector2 seperation = Vector2Scale(contact->normal, contact->depth / totalInverseMass);
		contact->body1->position = Vector2Add(contact->body1->position, Vector2Scale(seperation, contact->body1->inverseMass));
		contact->body2->position = Vector2Add(contact->body2->position, Vector2Scale(seperation, -contact->body2->inverseMass));
	}
}

void resolveContacts(nkContact_t* contacts) {
	for (nkContact_t* contact = contacts; contact; contact = contact->next) {
		Vector2 rv = Vector2Subtract(contact->body1->velocity, contact->body2->velocity);
		float nv = Vector2DotProduct(rv, contact->normal);

		if (nv > 0) continue;
		float totalInverseMass = (contact->body1->inverseMass + contact->body2->inverseMass);
		float impulseMagnitude = -(1 + contact->restitution) * nv / totalInverseMass;

		Vector2 impulse = Vector2Scale(contact->normal, impulseMagnitude);
		applyForce(contact->body1, impulse, FM_IMPULSE);
		applyForce(contact->body2, Vector2Negate(impulse), FM_IMPULSE);
	}
}