#include "raylib.h"
#include "raymath.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Utah Teapot");

    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 1.0f, 4.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model teapot = LoadModel("./teapot.obj");  
    SetModelMeshMaterial(&teapot, 0, 0);

    Shader shader = LoadShader(0, "./bloom.fs");

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    Vector3 tableTopSize = { 4.0f, 0.2f, 4.0f };
    Vector3 tableTopPosition = { 0.0f, 0.1f, 0.0f };
    float legHeight = 2.0f;
    float legThickness = 0.1f;
    Vector3 legSize = { legThickness, legHeight, legThickness };

    float angle = 0.0f;
    float radius = 15.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        angle += 0.005f;

        if (IsKeyDown(KEY_UP)) radius -= 0.05f;
        if (IsKeyDown(KEY_DOWN)) radius += 0.05f;

        if (radius < 1.0f) radius = 1.0f;

        camera.position.x = cos(angle) * radius;
        camera.position.z = sin(angle) * radius;

        camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };

        BeginTextureMode(target);
            ClearBackground(BLACK);

            BeginMode3D(camera);
                DrawCube(tableTopPosition, tableTopSize.x, tableTopSize.y, tableTopSize.z, BROWN);
                DrawCube((Vector3){ -1.8f, -1.0f, 1.8f }, legSize.x, legSize.y, legSize.z, BROWN);
                DrawCube((Vector3){ 1.8f, -1.0f, 1.8f }, legSize.x, legSize.y, legSize.z, BROWN);
                DrawCube((Vector3){ -1.8f, -1.0f, -1.8f }, legSize.x, legSize.y, legSize.z, BROWN);
                DrawCube((Vector3){ 1.8f, -1.0f, -1.8f }, legSize.x, legSize.y, legSize.z, BROWN);

                DrawModel(teapot, (Vector3){ 0.0f, tableTopPosition.y + tableTopSize.y/2 , 0.0f }, 0.5f, WHITE);
            EndMode3D();
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);

            BeginShaderMode(shader);
                DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);            
            EndShaderMode();

            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadShader(shader);
    UnloadModel(teapot);
    UnloadRenderTexture(target);

    CloseWindow();

    return 0;
}