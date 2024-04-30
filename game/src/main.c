#pragma region Includes
	#include "body.h"
	#include "raylib.h"
	#include "mathf.h"
	#include "raymath.h"
	#include "world.h"

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
		if (IsMouseButtonPressed(0)) {
			createBody(position);
		}

		Body* currentBody = bodies;
		while (currentBody != NULL) {
			// Update body position (this might be unnecessary for now)
			// currentBody->position = Vector2Add(currentBody->position, currentBody->velocity);

			currentBody = currentBody->next;
		}

		//render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("Frame: %.4f", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 20, MAGENTA);

		currentBody = bodies;
		while (currentBody != NULL) {
			DrawCircle((int)currentBody->position.x, (int)currentBody->position.y, 20, YELLOW);
			currentBody = currentBody->next;
		}

		EndDrawing();
	}
	CloseWindow();
	//free(bodies);
	return 0;
}