#include "force.h"
#include "body.h"
#include "mathf.h"

void applyGravitation(nkBody* bodies, float strength) {
	for (nkBody* body1 = bodies; body1; body1 = body1->next) {
		for (nkBody* body2 = bodies; body2; body2 = body2->next) {
			//<if bodies are the same, continue>
			if (body1 == body2) {
				continue;
			}

			Vector2 direction = Vector2Subtract(body1->position, body2->position); //< calculate direction(body position - body position)
			float distance = Vector2Length(direction);  //<get length of vector>

			distance = fmaxf(1, distance); //<clamp distance to a minumum of 1>
			float force = (body1->mass * body2->mass / (distance * distance))* strength;

			direction = Vector2Scale(Vector2Normalize(direction), force); //<scale normalized direction vector by force>;

			applyForce(body1, Vector2Scale(direction, -1), FM_FORCE); //<apply force to body 1, one of them is negative>
			applyForce(body2, direction, FM_FORCE); //<apply force to body 2, one of them is negative>
		}
	}
}