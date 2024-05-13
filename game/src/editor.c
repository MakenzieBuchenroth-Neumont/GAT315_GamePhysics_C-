#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
nkEditorData_t nkEditorData;

Vector2 anchor01 = { 872, 8 };
Vector2 anchor02 = { 880, 208 };
Vector2 anchor03 = { 880, 48 };
bool EditorBoxActive = true;

Texture2D cursorTexture;

void InitEditor() {
	GuiLoadStyle("raygui/styles/candy/style_candy.rgs");

	Image image = LoadImage("resources/reticle.png");
	cursorTexture = LoadTextureFromImage(image);
	UnloadImage(image);

	nkEditorData.gravitationScaleValue = 2;
	nkEditorData.massMaxValue = 0.1;
	nkEditorData.massMaxValue = 1;
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
