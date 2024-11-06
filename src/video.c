#include "video.h"
#include "raygui.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <mpeg2dec/mpeg2.h>
#include <mpeg2dec/mpeg2convert.h>

#define BUFFER_SIZE 4096

// TODO: make the below a struct as video_player
char *filePath;
bool videoLoaded = false;
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

void LoadVideo(const char *filename) {
  UpdateFilePath(filename);
  decoder = mpeg2_init();
  if (!decoder) {
    TraceLog(LOG_ERROR, "Failed to init the decoder.");
    exit(EXIT_FAILURE);
  }

  videoFile = fopen(filePath, "rb");
  if (!videoFile) {
    TraceLog(LOG_ERROR, "Failed to open the video file.");
    exit(EXIT_FAILURE);
  }

  info = mpeg2_info(decoder);
  videoLoaded = true;
}

void RenderVideo(void) {
  if (!videoLoaded)
    return;
  lastFrame = frameCount;
  while (lastFrame == frameCount && !paused) {
    state = mpeg2_parse(decoder);
    switch (state) {
    case STATE_BUFFER:
      size = fread(buffer, 1, BUFFER_SIZE, videoFile);
      mpeg2_buffer(decoder, buffer, buffer + BUFFER_SIZE);
      if (size == 0) {
        if (loop == true) {
          RestartVideo();
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
                 (Rectangle){332.0f, 100, 300, 200}, (Vector2){0, 0}, 0, WHITE);
  EndTextureMode();
}

void DrawVideo(void) {
  if (!videoLoaded)
    return;
  DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.width},
                 (Rectangle){450.0f, 100, 400, 300}, (Vector2){0, 0}, 0, WHITE);
}

void UnloadVideo(void) {
  UnloadRenderTexture(renderTexture);
  if (decoder != NULL) {
    mpeg2_close(decoder);
  }
  if (videoFile != NULL) {
    fclose(videoFile);
  }
}

void RestartVideo(void) {
  frameCount = 0;
  if (videoFile == NULL)
    return;
  rewind(videoFile);
  paused = false;
}

char *GetFilePath() { return filePath; }
void UpdateFilePath(const char *filename) {
  if (filePath != NULL) {
    free(filePath);
  }

  size_t length = strlen(filename) + 1;
  filePath = malloc(length);

  if (filePath != NULL) {
    snprintf(filePath, length, "%s", filename);
  } else {
    TraceLog(LOG_ERROR, "Memory allocation failed [UpdateFilePath]\n");
    exit(EXIT_FAILURE);
  }
}
