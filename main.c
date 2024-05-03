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

    Model teapot = LoadModel("./teapot.obj");  
    SetModelMeshMaterial(&teapot, 0, 0);

    float angle = 0.0; 
    float radius = 10.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        angle += 0.005f;

        if (IsKeyDown(KEY_UP)) radius -= 0.05f;
        if (IsKeyDown(KEY_DOWN)) radius += 0.05f;

        if (radius < 1.0f) radius = 1.0f;

        camera.position.x = cos(angle) * radius;
        camera.position.z = sin(angle) * radius;

        camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                DrawModel(teapot, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
                DrawGrid(10, 1.0f);
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadModel(teapot);

    CloseWindow();

    return 0;
}
