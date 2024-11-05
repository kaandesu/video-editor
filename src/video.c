#include "video.h"
#include "raygui.h"
#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <mpeg2dec/mpeg2.h>
#include <mpeg2dec/mpeg2convert.h>

#define BUFFER_SIZE 4096

static FILE *videoFile;
static mpeg2dec_t *decoder;
static Image img = {0};
static RenderTexture2D renderTexture = {0};
static Texture2D texture = {0};
static int frameCount, lastFrame = 0;
static bool paused = false;
static const mpeg2_info_t *info;
static mpeg2_state_t state;
static bool gotDims = false;
static bool loop = false;
static uint8_t buffer[BUFFER_SIZE];
static size_t size;

bool initVideo(const char *filename) {
  decoder = mpeg2_init();
  if (!decoder) {
    TraceLog(LOG_ERROR, "Failed to init the decoder.");
    return false;
  }

  videoFile = fopen(filename, "rb");
  if (!videoFile) {
    TraceLog(LOG_ERROR, "Failed to open the video file.");
    return false;
  }

  info = mpeg2_info(decoder);

  return true;
}

void updateVideo(void) {
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

        BeginDrawing();
        UpdateTexture(texture, info->display_fbuf->buf[0]);
        frameCount++;
        BeginTextureMode(renderTexture);
        DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.width},
                       (Rectangle){332.0f, 100, 400, 300}, (Vector2){0, 0}, 0,
                       WHITE);
        EndTextureMode();

        DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.width},
                       (Rectangle){332.0f, 100, 400, 300}, (Vector2){0, 0}, 0,
                       WHITE);
      }
      break;
    default:
      break;
    }
  }
}

int getCurrentFrameCount() { return frameCount; }

void renderVideo(void) {
  BeginTextureMode(renderTexture);
  DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.width},
                 (Rectangle){332.0f, 100, 400, 300}, (Vector2){0, 0}, 0, WHITE);
  EndTextureMode();
}

void drawVideo(void) {
  DrawFPS(10, 10);
  GuiPanel((Rectangle){304, 80, 456, 344}, NULL);
  DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.width},
                 (Rectangle){332.0f, 100, 400, 300}, (Vector2){0, 0}, 0, WHITE);
}

void unloadVideo(void) {
  UnloadRenderTexture(renderTexture);
  mpeg2_close(decoder);
  fclose(videoFile);
}

void restartVideo(void) {
  rewind(videoFile);
  frameCount = 0;
  paused = false;
}
