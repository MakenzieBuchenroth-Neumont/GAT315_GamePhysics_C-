#pragma region Includes
#include "body.h"
#include "raylib.h"
#include "mathf.h"
#include "raymath.h"
#include "world.h"
#include "integrator.h"
#include "force.h"

#include <stdlib.h>
#include <assert.h>
#pragma endregion

#define MAX_BODIES 100000
#define MAX_POINTS 20

//https://chat.openai.com/share/40b5a6e1-c9ca-4bbb-bec9-c849d2444986
int main(void) {
	InitWindow(1280, 720, "Pheesics Ingin");
	SetTargetFPS(60);

	// initialize world
	//nkGravity = (Vector2){ 0, 30 };
	nkGravity = (Vector2){ 0, 0 };

	// game loop
	while (!WindowShouldClose()) {
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonPressed(0)) {
			Color hsvColor = ColorFromHSV(getRandomFloatValue(0, 360), getRandomFloatValue(0, 100), getRandomFloatValue(100, 100));
			float angleIncrement = 360.0f / 20; // angle between each point of the star
			// circular,multicolored burst
			/*for (int i = 0; i < 50; i++) {
				nkBody* body = createBody(position);
				body->color.x = (float)hsvColor.r / 255.0f;
				body->color.y = (float)hsvColor.g / 255.0f;
				body->color.z = (float)hsvColor.b / 255.0f;
				body->mass = getRandomFloatValue(1, 10);
				body->inverseMass = 1 / body->mass;
				body->type = BT_DYNAMIC;
				body->damping = 2.5f;
				body->gravityScale = 20;
				Vector2 force = Vector2Scale(getVector2FromAngle(getRandomFloatValue(0, 360) * DEG2RAD), getRandomFloatValue(1000, 2000));
				applyForce(body, force, FM_IMPULSE);
			}*/
			// directed burst
			/*float angle = getRandomFloatValue(0, 360);
			for (int i = 0; i < 50; i++) {
				nkBody* body = createBody(position);
				body->color.x = (float)hsvColor.r / 255.0f;
				body->color.y = (float)hsvColor.g / 255.0f;
				body->color.z = (float)hsvColor.b / 255.0f;
				body->mass = getRandomFloatValue(1, 10);
				body->inverseMass = 1 / body->mass;
				body->type = BT_DYNAMIC;
				body->damping = 2.5f;
				body->gravityScale = 20;
				Vector2 force = Vector2Scale(getVector2FromAngle((angle + getRandomFloatValue(-30, 30)) * DEG2RAD), getRandomFloatValue(1000, 2000));
				applyForce(body, force, FM_IMPULSE);
			}*/
			// starburst
			/*for (int i = 0; i < 200; i++) {
				nkBody* body = createBody(position);
				body->color.x = (float)hsvColor.r / 255.0f;
				body->color.y = (float)hsvColor.g / 255.0f;
				body->color.z = (float)hsvColor.b / 255.0f;
				body->mass = getRandomFloatValue(1, 10);
				body->inverseMass = 1 / body->mass;
				body->type = BT_DYNAMIC;
				body->damping = 2.5f;
				body->gravityScale = 20;

				float angle = i * angleIncrement * DEG2RAD;

				Vector2 offset = Vector2Scale(getVector2FromAngle(angle),1000);

				applyForce(body, offset, FM_IMPULSE);
			}*/
		}

		// apply force
		//applyGravitation(nkBodies, 100);

		// update bodies
		for (nkBody* body = nkBodies; body; body = body->next) {
			step(body, dt);
		}

		//render
		BeginDrawing();
		ClearBackground(BLACK);

		//stats
		DrawText(TextFormat("FPS: %.2f (%.2f ms)", fps, 1000 / fps), 10, 10, 20, LIME);
		DrawText(TextFormat("Frame: %.4f", dt), 10, 30, 20, LIME);

		DrawCircle((int)position.x, (int)position.y, 20, MAGENTA);
		
		for (nkBody* body = nkBodies; body; body = body->next) {
			Color circleColor = { (unsigned char)(body->color.x * 255), (unsigned char)(body->color.y * 255), (unsigned char)(body->color.z * 255), 255 };
			DrawCircle((int)body->position.x, (int)body->position.y, body->mass, circleColor);
		}
		

		EndDrawing();
	}
	CloseWindow();
	return 0;
}