#include "render.h"
#include "raymath.h"

Vector2 nkScreenSize = { 1280, 720 }; // Setting the screen size to 1280x720 pixels
float nkScreenZoom = 1.0f; // Setting the screen zoom to default 1.0
float nkViewSize = 25.0f; // Setting the view size to 25 units

// Function to convert screen coordinates to world coordinates
Vector2 ConvertScreenToWorld(Vector2 screen) {
    float ratio = nkScreenSize.x / nkScreenSize.y; // Calculating aspect ratio
    Vector2 extents = (Vector2){ nkViewSize * ratio, nkViewSize }; // Calculating view extents
    extents = Vector2Scale(extents, nkScreenZoom); // Scaling extents based on screen zoom

    Vector2 lower = Vector2Negate(extents); // Calculating lower bounds of world coordinates
    Vector2 upper = extents; // Calculating upper bounds of world coordinates

    float nx = screen.x / nkScreenSize.x; // Normalizing screen x-coordinate
    float ny = (nkScreenSize.y - screen.y) / nkScreenSize.y; // Normalizing screen y-coordinate

    Vector2 world;
    world.x = ((1 - nx) * lower.x) + (nx * upper.x); // Converting normalized x-coordinate to world coordinate
    world.y = ((1 - ny) * lower.y) + (ny * upper.y); // Converting normalized y-coordinate to world coordinate

    return world; // Returning the converted world coordinates
}

// Function to convert world coordinates to screen coordinates
Vector2 ConvertWorldToScreen(Vector2 world) {
    float ratio = nkScreenSize.x / nkScreenSize.y; // Calculating aspect ratio
    Vector2 extents = (Vector2){ nkViewSize * ratio, nkViewSize }; // Calculating view extents
    extents = Vector2Scale(extents, nkScreenZoom); // Scaling extents based on screen zoom

    Vector2 lower = Vector2Negate(extents); // Calculating lower bounds of world coordinates
    Vector2 upper = extents; // Calculating upper bounds of world coordinates

    float nx = (world.x - lower.x) / (upper.x - lower.x); // Normalizing world x-coordinate
    float ny = (world.y - lower.y) / (upper.y - lower.y); // Normalizing world y-coordinate

    Vector2 screen;
    screen.x = nx * nkScreenSize.x; // Converting normalized x-coordinate to screen coordinate
    screen.y = (1.0f - ny) * nkScreenSize.y; // Converting normalized y-coordinate to screen coordinate

    return screen; // Returning the converted screen coordinates
}

// Function to convert world coordinates to pixels
float ConvertWorldToPixel(float world) {
    float ratio = nkScreenSize.x / nkScreenSize.y; // Calculating aspect ratio
    Vector2 extents = (Vector2){ nkViewSize * ratio, nkViewSize }; // Calculating view extents
    extents = Vector2Scale(extents, nkScreenZoom); // Scaling extents based on screen zoom

    float nx = world / extents.x; // Normalizing world coordinate
    float pixel = nx * nkScreenSize.x; // Converting normalized coordinate to pixel

    return pixel; // Returning the converted pixel value
}