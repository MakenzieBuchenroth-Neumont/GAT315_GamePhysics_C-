#pragma once
#include "raylib.h"
#include "stdlib.h"

inline float getRandomFloatValue01() {
	return rand() / (float)RAND_MAX;
}

inline float getRandomFloatValue(float min, float max) {
	return min + (max - min) * getRandomFloatValue01();
}

inline Vector2 createVector2(float x, float y) {
	return (Vector2) { x, y };
}