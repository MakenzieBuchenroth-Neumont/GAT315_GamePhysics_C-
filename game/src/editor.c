#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"
#include <body.h>
#include "render.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
nkEditorData_t nkEditorData;

Vector2 anchor01 = { 988, 8 };
Vector2 anchor02 = { 1000, 208 }; // main box
Vector2 anchor03 = { 1000, 48 };
bool EditorBoxActive = true;

Texture2D cursorTexture;

void InitEditor() {
	GuiLoadStyle("raygui/styles/candy/style_candy.rgs");

	Image image = LoadImage("resources/reticle.png");
	cursorTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	nkEditorData.gravitationScaleValue = 2;
	nkEditorData.massMinValue = 4.0;
	nkEditorData.massMaxValue = 7.0;
    nkEditorData.bodyDampingValue = 0.2f;
    nkEditorData.bodyGravityValue = 0.2f;

    nkEditorData.settingsActive = true;
}

void UpdateEditor(Vector2 position) {
	//
}

void DrawEditor(Vector2 position) {
    if (nkEditorData.DropdownBox004EditMode) GuiLock();

    if (nkEditorData.settingsActive)
    {
        nkEditorData.settingsActive = !GuiWindowBox((Rectangle) { anchor02.x + -8, anchor02.y + -200, 224, 312 }, "Settings");
        GuiSliderBar((Rectangle) { anchor02.x + 80, anchor02.y + 32, 120, 16 }, "Gravitation", NULL, &nkEditorData.gravitationScaleValue, 0, 10);
        GuiGroupBox((Rectangle) { anchor02.x + 0, anchor02.y + 8, 216, 80 }, "World");
    }
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 24, 120, 16 }, "Max Mass", NULL, &nkEditorData.massMaxValue, 0, 10);
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 48, 120, 16 }, "Min Mass", NULL, &nkEditorData.massMinValue, 0, 10);
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 72, 120, 16 }, "Body Damping", NULL, &nkEditorData.bodyDampingValue, 0, 10);
    GuiSliderBar((Rectangle) { anchor03.x + 80, anchor03.y + 96, 120, 16 }, "Body Gravity", NULL, &nkEditorData.bodyGravityValue, 0, 10);
    GuiGroupBox((Rectangle) { anchor01.x + 8, anchor01.y + 40, 216, 152 }, "Body");
    if (GuiDropdownBox((Rectangle) { anchor03.x + 80, anchor03.y + 120, 120, 24 }, "DYNAMIC;STATIC;KINEMATIC", &nkEditorData.DropdownBox004Active, nkEditorData.DropdownBox004EditMode)) nkEditorData.DropdownBox004EditMode = !nkEditorData.DropdownBox004EditMode;

	DrawTexture(cursorTexture, (int)position.x - (cursorTexture.width / 2) , position.y - (cursorTexture.height / 2), WHITE);

	GuiUnlock();
}

nkBody* getBodyIntersect(nkBody* bodies, Vector2 position) {
    for (nkBody* body = bodies; body; body = body->next) {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass))) {
            return body;
        }
    }

    return NULL;
}

void drawLineBodyToPosition(nkBody* body, Vector2 position) {
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, GREEN);
}
