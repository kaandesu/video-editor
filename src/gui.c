#include "gui.h"
#include "raygui.h"
#include "raylib.h"
#include "video.h"
#include <stdio.h>
#include <stdlib.h>

static Rectangle ScrollPanel000ScrollView = {0, 0, 0, 0};
static Vector2 ScrollOffset = {0, 0};
static Vector2 ScrollBoundsOffset = {0, 0};
static Color colorPickerVal = {255, 255, 255, 255};
static bool spinnerEditMode = false;
static int spinnerVal = 0;
static bool button4Pressed = false;
static bool restartBtnPressed = false;
static bool button7Pressed = false;

static void listenGui();
void drawGui(void) {
  DrawFPS(10, 10);
  GuiScrollPanel((Rectangle){320, 520, 616 - ScrollBoundsOffset.x,
                             168 - ScrollBoundsOffset.y},
                 NULL, (Rectangle){320, 520, 616, 168}, &ScrollOffset,
                 &ScrollPanel000ScrollView);
  GuiPanel((Rectangle){304, 80, 456, 344}, NULL);
  GuiColorPicker((Rectangle){792, 88, 96, 96}, NULL, &colorPickerVal);
  char frameCountLabel[50];
  snprintf(frameCountLabel, 50, "Frame count: %d\n", getCurrentFrameCount());
  GuiLabel((Rectangle){328, 448, 136, 32}, frameCountLabel);

  button4Pressed = GuiButton((Rectangle){520, 448, 144, 32}, "Upload");
  GuiLine((Rectangle){792, 200, 120, 16}, NULL);
  restartBtnPressed = GuiButton((Rectangle){792, 232, 120, 24}, "#58# Restart");
  button7Pressed = GuiButton((Rectangle){792, 272, 120, 24}, "Save");

  listenGui();
}

static void listenGui() {
  if (restartBtnPressed) {
    restartVideo();
  }
}

Color getColorPickerVal() { return colorPickerVal; }
