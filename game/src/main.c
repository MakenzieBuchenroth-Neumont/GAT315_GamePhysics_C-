#pragma region Includes
#include "body.h"
#include "raylib.h"
#include "mathf.h"
#include "raymath.h"
#include "world.h"
#include "integrator.h"
#include "force.h"
#include "render.h"
#include "editor.h"
#include "spring.h"

#include <stdlib.h>
#include <assert.h>
#pragma endregion

#define MAX_BODIES 100000
#define MAX_POINTS 20

//https://chat.openai.com/share/40b5a6e1-c9ca-4bbb-bec9-c849d2444986
int main(void) {

	nkBody* selectedBody = NULL;
	nkBody* connectBody = NULL;

	InitWindow(1280, 720, "Pheesics Ingin");
	InitEditor();
	HideCursor();
	SetTargetFPS(60);

	// initialize world
	//nkGravity = (Vector2){ 0, 30 };
	nkGravity = (Vector2){ 0, -1 };

	// game loop
	while (!WindowShouldClose()) {
		//update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();

		nkScreenZoom = Clamp(nkScreenZoom, 0.1f, 10);

		nkScreenZoom += GetMouseWheelMove() * 0.2f;

		UpdateEditor(position);

		selectedBody = getBodyIntersect(nkBodies, position);
		if (selectedBody) {
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines(screen.x, screen.y, ConvertWorldToPixel(selectedBody->mass) + 5, RED);
		}

		// create body
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Color hsvColor = ColorFromHSV(getRandomFloatValue(0, 360), getRandomFloatValue(0, 100), getRandomFloatValue(100, 100));
			float angleIncrement = 360.0f / 5; // angle between each point of the star
			int random = GetRandomValue(0, 2);
			if (random == 0) {
				// circular,multicolored burst
				for (int i = 0; i < 1; i++) {
					nkBody* body = createBody(ConvertScreenToWorld(position), getRandomFloatValue(nkEditorData.massMinValue, nkEditorData.massMaxValue), nkEditorData.DropdownBox004Active);
					body->position = ConvertScreenToWorld(position);
					body->color.x = (float)hsvColor.r / 255.0f;
					body->color.y = (float)hsvColor.g / 255.0f;
					body->color.z = (float)hsvColor.b / 255.0f;
					body->damping = 0; //2.5f;
					body->gravityScale = 0; //20;

					addBody(body);
					Vector2 force = Vector2Scale(getVector2FromAngle(getRandomFloatValue(0, 360) * DEG2RAD), getRandomFloatValue(1000, 2000));
				}
			}
			else if (random == 1) {
				// directed burst
				float angle = getRandomFloatValue(0, 360);
				for (int i = 0; i < 1; i++) {
					nkBody* body = createBody(ConvertScreenToWorld(position), getRandomFloatValue(nkEditorData.massMinValue, nkEditorData.massMaxValue), nkEditorData.DropdownBox004Active);
					
					body->color.x = (float)hsvColor.r / 255.0f;
					body->color.y = (float)hsvColor.g / 255.0f;
					body->color.z = (float)hsvColor.b / 255.0f;
					
					body->damping = 0; //2.5f;
					body->gravityScale = 0; //20;
					Vector2 force = Vector2Scale(getVector2FromAngle((angle + getRandomFloatValue(-30, 30)) * DEG2RAD), getRandomFloatValue(1000, 2000));
				}
			}
			else {
				// starburst
				for (int i = 0; i < 1; i++) {
					nkBody* body = createBody(ConvertScreenToWorld(position), getRandomFloatValue(nkEditorData.massMinValue, nkEditorData.massMaxValue), nkEditorData.DropdownBox004Active);
					
					body->color.x = (float)hsvColor.r / 255.0f;
					body->color.y = (float)hsvColor.g / 255.0f;
					body->color.z = (float)hsvColor.b / 255.0f;
					
					body->damping = 0; //2.5f;
					body->gravityScale = 0; //20;

					float angle = i * angleIncrement * DEG2RAD;

					Vector2 offset = Vector2Scale(getVector2FromAngle(angle), 1000);
				}
			}
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) connectBody = selectedBody;
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) drawLineBodyToPosition(connectBody, position);
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody) {
			if (selectedBody && selectedBody != connectBody) {
				nkSpring_t* spring = createSpring(connectBody, selectedBody, Vector2Distance(connectBody->position, selectedBody->position), 20);
				addSpring(spring);
			}
		}

		// apply force
		applyGravitation(nkBodies, nkEditorData.gravitationScaleValue);
		applySpringForce(nkSprings);

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

		//DrawCircle((int)position.x, (int)position.y, 20, MAGENTA);

		// draw springs
		for (nkSpring_t* spring = nkSprings; spring; spring = spring->next) {
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine((int)screen1.x, (int)screen1.y, (int)screen2.x, (int)screen2.y, RED);
		}

		// draw bodies
		for (nkBody* body = nkBodies; body; body = body->next) {
			Color circleColor = { (unsigned char)(body->color.x * 255), (unsigned char)(body->color.y * 255), (unsigned char)(body->color.z * 255), 255 };

			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), circleColor);
		}


		DrawEditor(position);

		EndDrawing();
	}
	CloseWindow();
	return 0;
}