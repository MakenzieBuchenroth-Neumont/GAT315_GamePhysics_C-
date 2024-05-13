#pragma once
#include "raylib.h"
#include "raymath.h"

extern Vector2 nkScreenSize;
extern float nkScreenZoom;
extern float nkViewSize;

Vector2 ConvertScreenToWorld(Vector2 screen);
Vector2 ConvertWorldToScreen(Vector2 world);
float ConvertWorldToPixel(float world);
