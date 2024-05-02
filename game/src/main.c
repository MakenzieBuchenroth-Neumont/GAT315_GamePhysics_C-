#pragma region Includes
#include "body.h"
#include "raylib.h"
#include "mathf.h"
#include "raymath.h"
#include "world.h"
#include "integrator.h"

#include <stdlib.h>
#include <assert.h>
#pragma endregion

#define MAX_BODIES 100000

//https://chat.openai.com/share/40b5a6e1-c9ca-4bbb-bec9-c849d2444986
int main(void) {
	InitWindow(1280, 720, "Pheesics Ingin");
	SetTargetFPS(60);

	// game loop
	while (!WindowShouldClose()) {
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0)) {
			nkBody* body = createBody(position);
			body->mass = getRandomFloatValue(1, 10);
		}

		// apply force
		nkBody* currentBody = nkBodies;
		while (currentBody != NULL) {
			applyForce(currentBody, createVector2(0, -10000));
			currentBody = currentBody->next;
		}

		// update bodies
		currentBody = nkBodies;
		while (currentBody != NULL) {
			//explicitEuler(currentBody, dt);
			semiImplicitEuler(currentBody, dt);
			clearForce(currentBody);
			currentBody = currentBody->next;
		}

		//render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("Frame: %.4f", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 20, MAGENTA);

		// draw bodies
		currentBody = nkBodies;
		while (currentBody != NULL) {
			DrawCircle((int)currentBody->position.x, (int)currentBody->position.y, currentBody->mass, YELLOW);
			currentBody = currentBody->next;
		}

		EndDrawing();
	}
	CloseWindow();
	//free(bodies);
	return 0;
}