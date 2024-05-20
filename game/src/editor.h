#pragma once
#include "raylib.h"

typedef struct nkEditorData {
    bool settingsActive;
    float gravitationScaleValue;
    bool DropdownBox004EditMode;
    int DropdownBox004Active;
    float bodyDampingValue;
    float bodyGravityValue;
    float gravityScale;

    float timestep;
    float mass;
    float gravity;

    float stiffness;
    float restitution;

    bool simulate;
    bool reset;
} nkEditorData_t;

extern nkEditorData_t nkEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);

struct nkBody* getBodyIntersect(struct nkBody* bodies, Vector2 position); 
void drawLineBodyToPosition(struct nkBody* body, Vector2 position);