#pragma once
#include "raylib.h"
#include <stdlib.h>

inline float getRandomFloatValue01() {
	return rand() / (float)RAND_MAX;
}

inline float getRandomFloatValue(float min, float max) {
	return min + (max - min) * getRandomFloatValue01();
}

inline Vector2 createVector2(float x, float y) {
	return (Vector2) { x, y };
}

/*inline Vector2 getVector2FromAngle(float angle) {
	Vector2 v;
	v.x = cosf(angle);
	v.y = sinf(angle);

	return v;
}*/

inline int getRandomIntValue01() {
	return rand() / (int)RAND_MAX;
}

inline int getRandomIntValue(int min, int max) {
	return min + (max - min) * getRandomIntValue01();
}