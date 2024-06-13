/*******************************************************************************************
*
*   raylib game template
*
*   <Texture Hot Reloader>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include <cstring>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#include <iostream>
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static constexpr int g_ScreenWidth = 720;
static constexpr int g_ScreenHeight = 1280;

static constexpr int g_Target_fps = 165;

static constexpr float g_CubeSize = 3.0f;

bool HasResourceChanged(void* loaded_data, void* external_data, size_t resource_size)
{
    // #TODO
    return false;
}

int main()
{
    // Initialization
    InitWindow(g_ScreenWidth, g_ScreenHeight, "Texture Hot Reloader");
    SetTargetFPS(g_Target_fps);

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 16.0f, 14.0f, 16.0f };     // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };          // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };              // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                    // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // Camera projection type

    Mesh cube_mesh = GenMeshCube(g_CubeSize, g_CubeSize, g_CubeSize);
    Model cube_model = LoadModelFromMesh(cube_mesh);
    Vector3 cube_position = { 0.0f, 0.0f, 0.0f };

    const char* texture_path = "resources/ice.png";
    Image image = LoadImage(texture_path);

    cube_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTextureFromImage(image);
    Texture2D& cube_texture_ref = cube_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture;

    // Pause camera orbital rotation (and zoom)
    bool pause = false;

    // Main loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // #TODO: Implement hot reloading

        // Update Input
        if (IsKeyPressed(KEY_P))
        {
            pause = !pause;
        }
        else if (IsKeyPressed(KEY_R)) // R can be pressed to force a reload
        {
            UnloadTexture(cube_texture_ref);
            cube_texture_ref = LoadTextureFromImage(LoadImage(texture_path));
        }

        if (!pause) UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camera);
                DrawModel(cube_model, cube_position, 1.0f, WHITE);
            EndMode3D();

            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadModel(cube_model);
    CloseWindow();
}
