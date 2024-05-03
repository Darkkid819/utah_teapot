#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

static const float teapotVertices[] = {
    // vertices data here
};
static const float teapotNormals[] = {
    // normals data here
};
static const unsigned int teapotIndices[] = {
    // indices data here
};

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
                
                rlPushMatrix();
                rlTranslatef(0.0f, 0.0f, 0.0f);
                rlBegin(4);
                for (int i = 0; i < sizeof(teapotIndices)/sizeof(teapotIndices[0]); i++) {
                    int idx = teapotIndices[i];
                    rlVertex3f(teapotVertices[3 * idx], teapotVertices[3 * idx + 1], teapotVertices[3 * idx + 2]);
                    rlNormal3f(teapotNormals[3 * idx], teapotNormals[3 * idx + 1], teapotNormals[3 * idx + 2]);
                }
                rlEnd();
                rlPopMatrix();
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
