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

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "kaan's video editor");
  GuiLoadStyleCyber();
  SetTargetFPS(60);
  SetExitKey(KEY_ESCAPE);

  setupGui();
  while (!WindowShouldClose()) {
    listenInput();
    RenderVideo();

    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    DrawVideo();
    drawGui();

    EndDrawing();
  }

  UnloadVideo();
  UnloadGui();
  CloseWindow();
  return EXIT_SUCCESS;
}
