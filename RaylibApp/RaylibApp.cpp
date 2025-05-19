// RaylibApp.cpp : Defines the entry point for the application.
//

#include "RaylibApp.h"
#include "raylib.h"

using namespace std;

int main()
{
	

    // Initialization
    //--------------------------------------------------------------------------------------
    Log::Init();
    const int screenWidth = 640;
    const int screenHeight = 320;
    InitWindow(screenWidth, screenHeight, "Chip8 Emulator");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < screenWidth / 10 + 1; i++)
        {
            DrawLineV(Vector2 { (float)10 * i, 0 }, Vector2{ (float)10 * i, (float)screenHeight }, LIGHTGRAY);
        }

        for (int i = 0; i < screenHeight / 10 + 1; i++)
        {
            DrawLineV(Vector2{ 0, (float)10* i }, Vector2{ (float)screenWidth, (float)10 * i }, LIGHTGRAY);
        }

        /*for (int i = 0; i < screenWidth / 10; i++)
        {
            for (int j = 0; j < screenHeight / 10; j++)
            {
                DrawText(TextFormat("[%i,%i]", i, j), 10 + 10 * i, 15 + 10 * j, 10, LIGHTGRAY);
            }
        }*/

        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    LOG_WARN("test");
	return 0;
}
