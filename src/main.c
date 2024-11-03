#include "raylib.h"

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

void restartVideo();

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "kaandesu video editor");
  SetTargetFPS(60);

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

  while (!WindowShouldClose()) {
    lastFrame = frameCount;
    while (lastFrame == frameCount) {
      state = mpeg2_parse(decoder);
      switch (state) {
      case STATE_BUFFER:
        size = fread(buffer, 1, BUFFER_SIZE, videoFile);
        mpeg2_buffer(decoder, buffer, buffer + BUFFER_SIZE);
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
    ClearBackground(DARKGRAY);
    if (GuiButton((Rectangle){100, 150 - 15, 120, 30}, "#58# Restart")) {
      restartVideo();
    }

    DrawFPS(10, 10);
    DrawTexturePro(
        texture, (Rectangle){0, 0, texture.width, texture.width},
        (Rectangle){(GetScreenWidth() / 2.0f) - 400.0f / 2, 0, 400, 300},
        (Vector2){0, 0}, 0, WHITE);
    EndDrawing();
  }

  UnloadTexture(texture);
  mpeg2_close(decoder);
  CloseWindow();
  return EXIT_SUCCESS;
}

void restartVideo() {
  rewind(videoFile);
  frameCount = 0;
}
