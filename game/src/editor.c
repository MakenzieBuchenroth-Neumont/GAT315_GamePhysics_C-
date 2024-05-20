#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"
#include <body.h>
#include "render.h"

#define EDITOR_DATA(data) TextFormat("%0.2f", data), &data

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
nkEditorData_t nkEditorData;

Vector2 anchor01 = { 990, 8 }; // body box
Vector2 anchor02 = { 1000, 208 }; // main box
Vector2 anchor03 = { 1000, 48 }; // world box
bool EditorBoxActive = true;

Texture2D cursorTexture;

void InitEditor() {
	GuiLoadStyle("raygui/styles/candy/style_candy.rgs");

	Image image = LoadImage("resources/reticle.png");
	cursorTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	nkEditorData.gravitationScaleValue = 2;
    nkEditorData.bodyDampingValue = 0.2f;
    nkEditorData.bodyGravityValue = 0.2f;

    nkEditorData.settingsActive = true;
    nkEditorData.gravityScale = 0.0f;

    nkEditorData.timestep = 50.0f;
    nkEditorData.mass = 2.5;
    nkEditorData.gravity = 1.0f;

    nkEditorData.restitution = 0.40f;
    nkEditorData.stiffness = 25;

    nkEditorData.simulate = true;
    nkEditorData.reset = false;
}

void UpdateEditor(Vector2 position) {
	//
}

void DrawEditor(Vector2 position) {

    if (nkEditorData.DropdownBox004EditMode) GuiLock();

    if (nkEditorData.settingsActive)
    {
        nkEditorData.settingsActive = !GuiWindowBox((Rectangle) { anchor02.x + -8, anchor02.y + -200, 232, 392 }, "Settings");
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 32, 100, 16 }, "Gravity", EDITOR_DATA(nkEditorData.bodyGravityValue), -10, 10);
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 56, 100, 16 }, "Gravitation", EDITOR_DATA(nkEditorData.gravitationScaleValue), 0, 100);
        GuiGroupBox((Rectangle) { anchor02.x + -1, anchor02.y + 25, 216, 120 }, "World");
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 80, 100, 16 }, "Timestep", EDITOR_DATA(nkEditorData.timestep), 0, 50);
    }
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 14, 100, 16 }, "Mass", EDITOR_DATA(nkEditorData.mass), 1, 10);
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 38, 100, 16 }, "Damping", EDITOR_DATA(nkEditorData.bodyDampingValue), 0, 100);
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 60, 100, 16 }, "Gravity Scale", EDITOR_DATA(nkEditorData.gravityScale), 0, 100);
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 86, 100, 16 }, "Stiffness (k)", EDITOR_DATA(nkEditorData.stiffness), 0, 50);
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 110, 100, 16 }, "Restitution", EDITOR_DATA(nkEditorData.restitution), 0, 1);
    GuiGroupBox((Rectangle) { anchor01.x + 8, anchor01.y + 40, 216, 175 }, "Body");
    if (GuiDropdownBox((Rectangle) { anchor03.x + 1, anchor03.y + 134, 210, 24 }, "STATIC;KINEMATIC;DYNAMIC", &nkEditorData.DropdownBox004Active, nkEditorData.DropdownBox004EditMode)) nkEditorData.DropdownBox004EditMode = !nkEditorData.DropdownBox004EditMode;

    nkEditorData.reset = GuiButton((Rectangle) { anchor01.x + 8, anchor01.y + 350, 108, 20 }, "Reset");
    GuiToggle((Rectangle) { anchor01.x + 118, anchor01.y + 350, 108, 20 }, "Simulate", &nkEditorData.simulate);

    DrawTexture(cursorTexture, (int)position.x - (cursorTexture.width / 2), position.y - (cursorTexture.height / 2), WHITE);

    GuiUnlock();
}

nkBody* getBodyIntersect(nkBody* bodies, Vector2 position) {
    for (nkBody* body = bodies; body; body = body->next) {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5f))) {
            return body;
        }
    }

    return NULL;
}

void drawLineBodyToPosition(nkBody* body, Vector2 position) {
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, GREEN);
}
