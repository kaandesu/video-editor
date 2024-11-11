#include "media_pool.h"
#include "file_dialog.h"
#include "raylib.h"
#include "style.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MediaPoolTitle "Media"

#define VIDEO_DEFAULT_COL DARKGRAY
#define AUDIO_DEFAULT_COL GRAY

#define boxWidth 100
#define boxHeight 35

Rectangle scrollView = {0, 0, 0, 0};
Vector2 mediaSourcesAreaOffset = {0, 0};
Vector2 panelScroll = {0, 0};
Rectangle panelView = {0};

// TODO: add icon based on type
// remove button
// info button
// open in finder for mac?
typedef struct MediaFile {
  enum MediaType type;
  Color color;
  char label[50];
  char *path;
} MediaFile;

typedef struct media_pool_window {
  FileDialog *fd;
  int count;
  MediaFile *MediaFiles;
} MediaPoolWindow;

void UpdateMediaPoolPaths(MediaPoolWindow *mpw);
static void setupDebug(MediaPoolWindow *mpw);

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
    UnloadDroppedFiles(GetFilePathList(mpw->fd));
  }

  for (int i = 0; i < mpw->count; i++) {
    float x = (panelRec.x + panelScroll.x + 12) * ((i % 2 != 0) + 1);
    float y = panelRec.y + panelScroll.y +
              ((i - (i % 2 != 0)) * (boxHeight + XXS) / 2.0f + XXS);
    DrawRectangle(x, y, boxWidth, boxHeight,
                  Fade(mpw->MediaFiles[i].color, .9f));
    DrawText(mpw->MediaFiles[i].label, x + 5, y + 2, 10, WHITE);
  }
  EndScissorMode();

  DrawFileDialog(mpw->fd);
}

MediaPoolWindow *LoadMediaPoolWindow(FileDialog *fd) {
  MediaPoolWindow *mpw = (MediaPoolWindow *)malloc(sizeof(MediaPoolWindow));
  if (mpw == NULL) {
    TraceLog(LOG_ERROR, "could not allocate MediaPoolWindow");
    exit(EXIT_FAILURE);
  }
  mpw->fd = fd;
  setupDebug(mpw);

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
  int filesCount = GetFilePathList(mpw->fd).count;

  mpw->MediaFiles =
      realloc(mpw->MediaFiles, (mpw->count + filesCount) * sizeof(MediaFile));
  if (mpw->MediaFiles == NULL) {
    TraceLog(LOG_ERROR, "Failed to realloc MediaFiles");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < filesCount; i++) {
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

    mpw->MediaFiles[mpw->count + i].path = strdup(fullPath);
    if (mpw->MediaFiles[mpw->count + i].path == NULL) {
      TraceLog(LOG_ERROR, "Failed to store path in MediaFile");
      exit(EXIT_FAILURE);
    }

    mpw->MediaFiles[mpw->count + i].color = VIDEO_DEFAULT_COL;
    strncpy(mpw->MediaFiles[mpw->count + i].label, fileName,
            sizeof(mpw->MediaFiles[mpw->count + i].label) - 1);
    mpw->MediaFiles[mpw->count + i]
        .label[sizeof(mpw->MediaFiles[mpw->count + i].label) - 1] = '\0';

    printf("Loaded media: %s\n", mpw->MediaFiles[mpw->count + i].label);
    free(pathCopy);
  }

  mpw->count += filesCount;
}

static void setupDebug(MediaPoolWindow *mpw) {
  mpw->MediaFiles = malloc(sizeof(MediaFile));
  if (mpw->MediaFiles == NULL) {
    fprintf(stderr, "Failed to allocate memory for MediaFiles\n");
    exit(EXIT_FAILURE);
  }

  mpw->MediaFiles[0].path = strdup("./resources/test.mpg");
  if (mpw->MediaFiles[0].path == NULL) {
    fprintf(stderr, "Failed to allocate memory for default path\n");
    exit(EXIT_FAILURE);
  }

  mpw->MediaFiles[0].color = VIDEO_DEFAULT_COL;
  strncpy(mpw->MediaFiles[0].label, "test.mpg",
          sizeof(mpw->MediaFiles[0].label) - 1);
  mpw->MediaFiles[0].label[sizeof(mpw->MediaFiles[0].label) - 1] = '\0';

  mpw->count = 1;
}
