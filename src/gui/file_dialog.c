#include "file_dialog.h"
#include "raygui.h"
#include "raylib.h"
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
  Rectangle rectangle;
  DragField *dragField;
  bool clicked;
  bool hovered;
  FilePathList fileList;
} FileDialog;

FileDialog *LoadFileDialog(Rectangle rect, char *label, char *wTitle,
                           char *wDesc, Vector2 pos) {
  FileDialog *fd = (FileDialog *)malloc(sizeof(FileDialog));
  if (fd == NULL) {
    TraceLog(LOG_ERROR, "could not allocate file dialog");
    exit(EXIT_FAILURE);
  }

  fd->rectangle = rect;
  snprintf(fd->label, sizeof(fd->label), "%s", label);

  fd->dragField = (DragField *)malloc(sizeof(DragField));

  if (fd->dragField == NULL) {
    TraceLog(LOG_ERROR, "error while allocating the dragField");
    exit(EXIT_FAILURE);
  }
  fd->dragField->active = false;
  fd->dragField->anchor = pos;

  snprintf(fd->dragField->title, sizeof(fd->dragField->title), "%s", wTitle);
  snprintf(fd->dragField->desc, sizeof(fd->dragField->desc), "%s", wDesc);

  return fd;
}

void DrawFileDialog(FileDialog *fd) {
  fd->clicked = GuiButton(fd->rectangle, fd->label);
  if (fd->dragField == NULL) {
    return;
  }
  DragField *df = fd->dragField;
  if (fd->clicked == true) {
    df->active = true;
  }

  if (df->active) {
    df->active = !GuiWindowBox(
        (Rectangle){df->anchor.x + 0, df->anchor.y + 0, 288, 208}, df->title);

    GuiLabel((Rectangle){df->anchor.x + 72, df->anchor.y + 96, 152, 24},
             df->desc);

    if (CheckCollisionPointRec(
            GetMousePosition(),
            (Rectangle){df->anchor.x + 0, df->anchor.y + 0, 288, 208})) {
      if (!fd->hovered) {
        fd->hovered = true;
        TraceLog(LOG_WARNING, "hovered on the thing");
      }
    } else {

      if (fd->hovered) {

        fd->hovered = false;
        TraceLog(LOG_WARNING, "unhovered on the thing");
      }
    }
  }

  if (IsFileDropped()) {
    if (!fd->hovered) {
      TraceLog(LOG_WARNING, "'unloading' the dropped files");
      char **tempList = malloc(sizeof(char *));
      tempList[0] = malloc(1);
      FilePathList tempFileList = {.count = 1, .paths = tempList};
      UnloadDroppedFiles(tempFileList);
    } else {
      TraceLog(LOG_WARNING, "loading the dropped files");
      fd->fileList = LoadDroppedFiles();
      if (fd->fileList.count == 1) {
        // TODO: check if is an .mpg file
        LoadVideo(fd->fileList.paths[0]);
        UnloadDroppedFiles(fd->fileList);
        df->active = false;
      }
    }
  }
}

void UnloadFileDialog(FileDialog *fd) { UnloadDroppedFiles(fd->fileList); }
