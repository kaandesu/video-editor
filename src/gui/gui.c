#include "gui.h"
#include "file_dialog.h"
#include "raygui.h"
#include "raylib.h"
#include "video.h"
#include <stdio.h>
#include <stdlib.h>

static float duration = 5.0f;

static bool uploadButton = false;
static bool restartButton = false;
static bool saveButton = false;

static FileDialog *fileImport;

static void inputGui();

void setupGui(void) {
  fileImport = LoadFileDialog((Rectangle){100, 100, 150, 24}, "Import File",
                              "IMPORT VIDEO", "DRAG & DROP THE VIDEO",
                              (Vector2){440, 200});
}

void drawGui(void) {
  char frameCountLabel[50];
  snprintf(frameCountLabel, 50, "Frame count: %d\n", getCurrentFrameCount());
  GuiLabel((Rectangle){328, 448, 136, 32}, frameCountLabel);

  uploadButton = GuiButton((Rectangle){520, 448, 144, 32}, "Upload");
  GuiLine((Rectangle){792, 200, 120, 16}, NULL);
  restartButton = GuiButton((Rectangle){792, 232, 120, 24}, "#58# Restart");
  saveButton = GuiButton((Rectangle){792, 272, 120, 24}, "Save");

  DrawFileDialog(fileImport);
  inputGui();
}

static void inputGui() {
  if (restartButton) {
    restartVideo();
  }
  if (saveButton) {
    restartVideo();
    // open a dialog, select sthe start and end
    // jump to framecount and wait until the duration * fps
    // open ffmpeg listening stdin
  }
}

void UnloadGui() { UnloadFileDialog(fileImport); }
