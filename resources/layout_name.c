/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    Rectangle ScrollPanel000ScrollView = { 0, 0, 0, 0 };
    Vector2 ScrollPanel000ScrollOffset = { 0, 0 };
    Vector2 ScrollPanel000BoundsOffset = { 0, 0 };
    Color ColorPicker002Value = { 0, 0, 0, 0 };
    bool Spinner004EditMode = false;
    int Spinner004Value = 0;
    bool Button004Pressed = false;
    bool Button006Pressed = false;
    bool Button007Pressed = false;
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            GuiScrollPanel((Rectangle){ 440, 368, 464 - ScrollPanel000BoundsOffset.x, 120 - ScrollPanel000BoundsOffset.y}, NULL, (Rectangle){ 440, 368, 464, 120 }, &ScrollPanel000ScrollOffset, &ScrollPanel000ScrollView);
            GuiPanel((Rectangle){ 440, 104, 264, 200 }, NULL);
            GuiColorPicker((Rectangle){ 728, 112, 96, 96 }, NULL, &ColorPicker002Value);
            if (GuiSpinner((Rectangle){ 440, 320, 120, 24 }, "SAMPLE TEXT", &Spinner004Value, 0, 100, Spinner004EditMode)) Spinner004EditMode = !Spinner004EditMode;
            Button004Pressed = GuiButton((Rectangle){ 576, 320, 120, 24 }, "SAMPLE TEXT"); 
            GuiLine((Rectangle){ 728, 224, 120, 16 }, NULL);
            Button006Pressed = GuiButton((Rectangle){ 728, 248, 120, 24 }, "SAMPLE TEXT"); 
            Button007Pressed = GuiButton((Rectangle){ 728, 288, 120, 24 }, "SAMPLE TEXT"); 
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

