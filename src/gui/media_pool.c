#include "media_pool.h"
#include "file_dialog.h"
#include "raylib.h"
#include "style.h"
#include "video.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define X_OFFSET 376

#define MediaPoolTitle "Media"
#define MediaPLayerTitle "Media Player"

#define boxWidth 100
#define boxHeight 35

const char *playText = ICON_PLAYER_PLAY;
const char *currentTimeLabel = "00:00:00/00:00:00";

Rectangle scrollView = {0, 0, 0, 0};
Vector2 mediaSourcesAreaOffset = {0, 0};
Vector2 panelScroll = {0, 0};
Rectangle panelView = {0};

typedef struct media_pool_window {
  FileDialog *fd;
  int count;
  char **pathList;
} MediaPoolWindow;

void UpdateMediaPoolPaths(MediaPoolWindow *mpw);

static void noop(void) {}

Rectangle panelContentRec = (Rectangle){0, 0, 230, 500};

void DrawMediaPoolWindow(MediaPoolWindow *mpw) {
  Rectangle panelRec = (Rectangle){96, 112, 244 - mediaSourcesAreaOffset.x,
                                   320 - mediaSourcesAreaOffset.y};
  GuiGroupBox((Rectangle){96, 72, 244 - mediaSourcesAreaOffset.x, 360},
              MediaPoolTitle);
  GuiScrollPanel(panelRec, NULL, panelContentRec, &panelScroll, &scrollView);

  /* Content */
  BeginScissorMode(scrollView.x, scrollView.y, scrollView.width,
                   scrollView.height);

  GuiGrid((Rectangle){panelRec.x + panelScroll.x, panelRec.y + panelScroll.y,
                      panelContentRec.width, panelContentRec.height},
          NULL, 46, 3, NULL);

  if (ShouldSavePaths(mpw->fd)) {
    UpdateMediaPoolPaths(mpw);
    savedPathsToPool(mpw->fd);
  }

  for (int i = 0; i < mpw->count; i++) {
    float x = (panelRec.x + panelScroll.x + 12) * ((i % 2 != 0) + 1);
    float y = panelRec.y + panelScroll.y +
              ((i - (i % 2 != 0)) * (boxHeight + XXS) / 2.0f + XXS);
    DrawRectangle(x, y, boxWidth, boxHeight, Fade(DARKGRAY, .9f));
    DrawText(mpw->pathList[i], x + 5, y + 2, 10, WHITE);
  }
  EndScissorMode();
  /* End Content */

  DrawFileDialog(mpw->fd);

  // TODO: move the media player below to its own file
  GuiGroupBox((Rectangle){X_OFFSET, 72, 544, 360}, MediaPLayerTitle);
  if (GuiButton((Rectangle){600, 392, MD, SM}, playText))
    RestartVideo();
  if (GuiButton((Rectangle){664, 392, MD, SM}, ICON_RESTART))
    RestartVideo();
  GuiLabel((Rectangle){392, 392, 128, 24}, currentTimeLabel);
}

MediaPoolWindow *LoadMediaPoolWindow(FileDialog *fd) {
  MediaPoolWindow *mpw = (MediaPoolWindow *)malloc(sizeof(MediaPoolWindow));
  if (mpw == NULL) {
    TraceLog(LOG_ERROR, "could not allocate MediaPoolWindow");
    exit(EXIT_FAILURE);
  }
  mpw->fd = fd;

  return mpw;
}

void UnloadMediaPoolWindow(MediaPoolWindow *mpw) {
  if (mpw == NULL)
    return;
  if (mpw->fd != NULL) {
    UnloadFileDialog(mpw->fd);
    mpw->fd = NULL;
  }
  free(mpw);
}

void UpdateMediaPoolPaths(MediaPoolWindow *mpw) {
  int list1_size = GetFilePathList(mpw->fd).count;

  mpw->pathList =
      realloc(mpw->pathList, (mpw->count + list1_size) * sizeof(char *));
  if (mpw->pathList == NULL) {
    TraceLog(LOG_ERROR, "Failed to realloc pathList");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < list1_size; i++) {
    char *fullPath = GetFilePathList(mpw->fd).paths[i];
    char *pathCopy = strdup(fullPath);
    if (pathCopy == NULL) {
      TraceLog(LOG_ERROR, "Failed to duplicate path");
      exit(EXIT_FAILURE);
    }

    char *token = strtok(pathCopy, "/");
    char *fileName = token;
    while (token != NULL) {
      fileName = token;
      token = strtok(NULL, "/");
    }

    mpw->pathList[mpw->count + i] = strdup(fileName);
    if (mpw->pathList[mpw->count + i] == NULL) {
      TraceLog(LOG_ERROR, "Failed to store file name in pathList");
      exit(EXIT_FAILURE);
    }

    printf("Loaded media: %s\n", mpw->pathList[mpw->count + i]);
    free(pathCopy);
  }

  mpw->count += list1_size;
}
