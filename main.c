#include "raylib.h"
#include "raymath.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Utah Teapot");

    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float angle = 0.0; 

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        angle += 0.005f;
        camera.position.x = cos(angle) * 4.0f;
        camera.position.z = sin(angle) * 4.0f;

        camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawGrid(10, 1.0f);
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
