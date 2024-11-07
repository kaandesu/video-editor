#include "file_dialog.h"
#include "raygui.h"
#include "raylib.h"
#include "style.h"
#include "video.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct DragField {
  char title[100];
  char desc[100];
  Vector2 anchor;
  bool active;
} DragField;

typedef struct file_dialog {
  char label[100];
  char displayLabel[100];
  Rectangle rectangle;
  DragField *dragField;
  bool clicked;
  bool hovered;
  bool once;
  bool shouldSavePaths;
  FilePathList fileList;
} FileDialog;

void savedPathsToPool(FileDialog *fd) { fd->shouldSavePaths = false; }

FileDialog *LoadFileDialog(Rectangle rect, const char *label,
                           const char *wTitle, char *wDesc, Vector2 pos) {
  FileDialog *fd = (FileDialog *)malloc(sizeof(FileDialog));
  if (fd == NULL) {
    TraceLog(LOG_ERROR, "could not allocate file dialog");
    exit(EXIT_FAILURE);
  }

  fd->rectangle = rect;
  fd->once = false;
  fd->shouldSavePaths = false;

  snprintf(fd->label, sizeof(fd->label), "%s", label);
  snprintf(fd->displayLabel, sizeof(fd->label), "%s", label);

  fd->dragField = (DragField *)malloc(sizeof(DragField));
  if (fd->dragField == NULL) {
    TraceLog(LOG_ERROR, "error while allocating the dragField");
    exit(EXIT_FAILURE);
  }

  fd->dragField->active = false;
  fd->dragField->anchor = pos;

  if (wTitle != NULL) {
    snprintf(fd->dragField->title, sizeof(fd->dragField->title), "%s", wTitle);
  }

  if (wDesc != NULL) {
    snprintf(fd->dragField->desc, sizeof(fd->dragField->desc), "%s", wDesc);
  }

  return fd;
}

void DrawFileDialog(FileDialog *fd) {
  fd->clicked = GuiButton(fd->rectangle, fd->displayLabel);
  if (fd->dragField == NULL) {
    return;
  }
  DragField *df = fd->dragField;
  if (fd->clicked == true) {
    df->active = !df->active;
  }

  uint8_t scrollbarWidth = GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH);
  Rectangle dfRect = (Rectangle){df->anchor.x + 0, df->anchor.y + 0,
                                 248 - scrollbarWidth - 6, 320};

  if (df->active) {
    snprintf(fd->displayLabel, sizeof(fd->displayLabel), "%s",
             ICON_CROSS " Close");
    GuiGroupBox(dfRect, df->title);

    DrawRectangle(dfRect.x, dfRect.y, dfRect.width, dfRect.height,
                  Fade(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)), 0.8));
    GuiLabel((Rectangle){df->anchor.x + 40, df->anchor.y + 128, 152, 24},
             df->desc);

    if (CheckCollisionPointRec(GetMousePosition(), dfRect)) {
      if (!fd->hovered)
        fd->hovered = true;
    } else if (fd->hovered) {
      fd->hovered = false;
    }
    fd->once = false;
  } else {
    if (!fd->once) {
      fd->once = true;
      snprintf(fd->displayLabel, sizeof(fd->displayLabel), "%s", fd->label);
    }
  }

  if (IsFileDropped()) {
    // TODO: handle multiple files
    if (!fd->hovered || !fd->dragField->active) {
      TraceLog(LOG_WARNING, "ignoring the dropped files");
      UnloadDroppedFiles(LoadDroppedFiles());
    } else {
      TraceLog(LOG_INFO, "loading the dropped files");
      fd->fileList = LoadDroppedFiles();
      if (fd->fileList.count >= 1) {
        for (int i = 0; i < fd->fileList.count; i++) {
          if (!IsFileExtension(fd->fileList.paths[i], ".mpg")) {
            TraceLog(LOG_WARNING, TextFormat("not supported extension: %s",
                                             fd->fileList.paths[i]));
            df->active = false;
            UnloadDroppedFiles(LoadDroppedFiles());
            return;
          }
          fd->shouldSavePaths = true;
        }
        LoadVideo(fd->fileList.paths[0]);
        df->active = false;
      }
    }
  }
}

FilePathList GetFilePathList(FileDialog *fd) { return fd->fileList; }
bool ShouldSavePaths(FileDialog *fd) { return fd->shouldSavePaths; }

void UnloadFileDialog(FileDialog *fd) {
  if (fd == NULL)
    return;

  UnloadDroppedFiles(fd->fileList);
  if (fd->dragField != NULL) {
    free(fd->dragField);
    fd->dragField = NULL;
  }

  free(fd);
}
