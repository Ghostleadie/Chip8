// RaylibApp.cpp : Defines the entry point for the application.
//

#include "RaylibApp.h"
#include "raylib.h"

#define XBOX_ALIAS_1 "xbox"
#define XBOX_ALIAS_2 "x-box"
#define PS_ALIAS     "playstation"

using namespace std;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Log::Init();
    const int screenWidth = 640;
    const int screenHeight = 320;
    InitWindow(screenWidth, screenHeight, "Chip8 Emulator");

    SetExitKey(KEY_NULL);       // Disable KEY_ESCAPE to close window, X-button still works

    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;    // Flag to set window to exit

    screens currentScreen = Logo;

    int framesCounter = 0;

    const float leftStickDeadzoneX = 0.1f;
    const float leftStickDeadzoneY = 0.1f;
    const float rightStickDeadzoneX = 0.1f;
    const float rightStickDeadzoneY = 0.1f;
    const float leftTriggerDeadzone = -0.9f;
    const float rightTriggerDeadzone = -0.9f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exitWindow)
    {
        // Update
        //----------------------------------------------------------------------------------
        // Detect if X-button or KEY_ESCAPE have been pressed to close window
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
        {
            exitWindowRequested = true;
        }

        if (exitWindowRequested)
        {
            // A request for close window has been issued, we can save data before closing
            // or just show a message asking for confirmation

            if (IsKeyPressed(KEY_Y)) exitWindow = true;
            else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }

        switch (currentScreen)
        {
            case Logo:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = Title;
                }
            } break;
            case Menu:
            {
                // TODO: Update Menu screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP) || IsGamepadButtonDown(0,GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
                {
                    currentScreen = Title;
                }
            } break;
            case Title:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
                {
                    currentScreen = Gameplay;
                }
            } break;
            case Gameplay:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
                {
                    currentScreen = Ending;
                }
            } break;
            case Ending:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
                {
                    currentScreen = Menu;
                }
            } break;
            default: break;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
            case Logo:
            {
                // TODO: Draw LOGO screen here!
                DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

            } break;
            case Menu:
            {
                // TODO: Draw Menu screen here!
                DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                DrawText("MENU SCREEN", 20, 20, 40, DARKGREEN);
                DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

            } break;
            case Title:
            {
                // TODO: Draw TITLE screen here!
                DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

            } break;
            case Gameplay:
            {
                for (int i = 0; i < screenWidth / 10 + 1; i++)
                {
                    DrawLineV(Vector2{ (float)10 * i, 0 }, Vector2{ (float)10 * i, (float)screenHeight }, LIGHTGRAY);
                }

                for (int i = 0; i < screenHeight / 10 + 1; i++)
                {
                    DrawLineV(Vector2{ 0, (float)10 * i }, Vector2{ (float)screenWidth, (float)10 * i }, LIGHTGRAY);
                }
                DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

            } break;
            case Ending:
            {
                // TODO: Draw ENDING screen here!
                DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

            } break;
            default:
            {
                break;
            }

            if (exitWindowRequested)
            {
                DrawRectangle(0, screenHeight / 2, screenWidth, screenHeight / 4, BLACK);
                DrawText("Are you sure you want to exit program? [Y/N]", 40, screenHeight / 2, 15, WHITE);
            }
        }

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
