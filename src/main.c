#include "raylib.h"
#include <stdbool.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mpeg2dec/mpeg2.h>
#include <mpeg2dec/mpeg2convert.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

#define VIDEO "resources/test.mpg"

#define BUFFER_SIZE 4096

FILE *videoFile;
int frameCount, lastFrame = 0;
bool paused = false;

void restartVideo();

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "kaandesu video editor");
  SetTargetFPS(60);

  Rectangle ScrollPanel000ScrollView = {0, 0, 0, 0};
  Vector2 ScrollOffset = {0, 0};
  Vector2 ScrollBoundsOffset = {0, 0};
  Color colorPickerVal = {255, 255, 255, 255};
  bool spinnerEditMode = false;
  int spinnerVal = 0;
  bool button4Pressed = false;
  bool restartBtnPressed = false;
  bool button7Pressed = false;

  mpeg2dec_t *decoder = mpeg2_init();
  if (!decoder) {
    TraceLog(LOG_ERROR, "could not init the decoder");
    exit(EXIT_FAILURE);
  }
  const mpeg2_info_t *info = mpeg2_info(decoder);
  mpeg2_state_t state;
  size_t size;
  videoFile = fopen(VIDEO, "rb");
  if (!videoFile) {
    TraceLog(LOG_ERROR, "could not read from the video file");
    exit(EXIT_FAILURE);
  }

  Image img = {0};
  Texture texture = {0};
  uint8_t buffer[BUFFER_SIZE];
  bool gotDims = false;
  bool loop = false;

  while (!WindowShouldClose()) {
    lastFrame = frameCount;
    while (lastFrame == frameCount && !paused) {
      state = mpeg2_parse(decoder);
      switch (state) {
      case STATE_BUFFER:
        size = fread(buffer, 1, BUFFER_SIZE, videoFile);
        mpeg2_buffer(decoder, buffer, buffer + BUFFER_SIZE);
        if (size == 0) {
          if (loop == true) {
            restartVideo();
          } else {
            paused = true;
          }
        }
        break;
      case STATE_SEQUENCE:
        mpeg2_convert(decoder, mpeg2convert_rgb24, NULL);
        break;
      case STATE_INVALID_END:
      case STATE_END:
      case STATE_SLICE:
        if (info->display_fbuf) {
          if (gotDims == false) {
            gotDims = true;

            img.width = info->sequence->width;
            img.height = info->sequence->height;
            img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
            img.mipmaps = 1;
            img.data = (unsigned char *)malloc(img.width * img.height * 3);

            texture = LoadTextureFromImage(img);
            UnloadImage(img);
          }
          UpdateTexture(texture, info->display_fbuf->buf[0]);
          frameCount++;
        }
        break;
      default:
        break;
      }
    }

    if (IsKeyDown(KEY_R)) {
      restartVideo();
    }

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    GuiScrollPanel((Rectangle){320, 520, 616 - ScrollBoundsOffset.x,
                               168 - ScrollBoundsOffset.y},
                   NULL, (Rectangle){320, 520, 616, 168}, &ScrollOffset,
                   &ScrollPanel000ScrollView);
    GuiPanel((Rectangle){304, 80, 456, 344}, NULL);
    GuiColorPicker((Rectangle){792, 88, 96, 96}, NULL, &colorPickerVal);
    GuiSpinner((Rectangle){328, 448, 136, 32}, "Current Frame", &frameCount, 0,
               100, true);
    button4Pressed = GuiButton((Rectangle){520, 448, 144, 32}, "Upload");
    GuiLine((Rectangle){792, 200, 120, 16}, NULL);
    restartBtnPressed =
        GuiButton((Rectangle){792, 232, 120, 24}, "#58# Restart");
    button7Pressed = GuiButton((Rectangle){792, 272, 120, 24}, "Save");

    if (restartBtnPressed) {
      restartVideo();
    }

    DrawFPS(10, 10);
    Color newCol =
        (Color){colorPickerVal.r, colorPickerVal.g, colorPickerVal.b, 255};
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.width},
                   (Rectangle){332.0f, 100, 400, 300}, (Vector2){0, 0}, 0,
                   newCol);
    EndDrawing();
  }

  UnloadTexture(texture);
  mpeg2_close(decoder);
  CloseWindow();
  return EXIT_SUCCESS;
}

void restartVideo() {
  rewind(videoFile);
  paused = false;
  frameCount = 0;
}
