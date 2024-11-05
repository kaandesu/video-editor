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

#define VIDEO "resources/test.mpg"

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "kaan's video editor");
  GuiLoadStyleCyber();
  SetTargetFPS(60);
  SetExitKey(KEY_ESCAPE);

  if (!initVideo(VIDEO)) {
    CloseWindow();
    return EXIT_FAILURE;
  }
  setupGui();
  while (!WindowShouldClose()) {
    listenInput();
    updateVideo();
    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    drawVideo();
    drawGui();
    EndDrawing();
  }

  unloadVideo();
  CloseWindow();
  return EXIT_SUCCESS;
}
