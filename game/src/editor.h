#pragma once
#include "raylib.h"

typedef struct nkEditorData {
    bool settingsActive;
    float massMaxValue;
    float gravitationScaleValue;
    bool DropdownBox004EditMode;
    int DropdownBox004Active;
    float massMinValue;
    float bodyDampingValue;
    float bodyGravityValue;
} nkEditorData_t;

extern nkEditorData_t nkEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);