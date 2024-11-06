#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "gui.h"
#include "style_cyber.h"
#include "video.h"

#include "input.h"

#define SCREEN_WIDTH 1100
#define SCREEN_HEIGHT 730

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "kaan's video editor");
  GuiLoadStyleCyber();
  SetTargetFPS(60);
  SetExitKey(KEY_ESCAPE);

  GuiSetup();
  while (!WindowShouldClose()) {
    listenInput();
    RenderVideo();

    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    DrawVideo();
    DrawGui();

    EndDrawing();
  }

  UnloadVideo();
  UnloadGui();
  CloseWindow();
  return EXIT_SUCCESS;
}
