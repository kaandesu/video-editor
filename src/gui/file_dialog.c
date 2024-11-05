#include "file_dialog.h"
#include "raygui.h"
#include "raylib.h"
#include "video.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
  if (!df->active)
    return;
  df->active = !GuiWindowBox(
      (Rectangle){df->anchor.x + 0, df->anchor.y + 0, 288, 208}, df->title);

  GuiLabel((Rectangle){df->anchor.x + 72, df->anchor.y + 96, 152, 24},
           df->desc);

  Vector2 mousePos = GetMousePosition();
  if (CheckCollisionPointRec(
          mousePos,
          (Rectangle){df->anchor.x + 0, df->anchor.y + 0, 288, 208})) {
    if (IsFileDropped()) {
      fd->fileList = LoadDroppedFiles();
      if (fd->fileList.count == 1) {
        // TODO: check if is an .mpg file
        LoadVideo(fd->fileList.paths[0]);
        df->active = false;
      } else {
        // TODO: create toast message here
      }
    }
  }
}

void UnloadFileDialog(FileDialog *fd) { UnloadDroppedFiles(fd->fileList); }
