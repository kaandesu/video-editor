#include "gui.h"
#include "file_dialog.h"
#include "raygui.h"
#include "raylib.h"
#include "video.h"
#include <stdio.h>

static float duration = 5.0f;

static bool uploadButton = false;
static bool restartButton = false;
static bool saveButton = false;
static FileDialog *fileImport;
static void GuiInput();

// NEW
const char *newBtnText = "new";
const char *loadLayoutBtnText = "load";
const char *downloadLayoutBtnText = "downl";
const char *exportVideoBtnText = "exprt";
const char *undoText = "back";
const char *redoText = "next";
const char *donateText = "donate";
const char *infoText = "info";
const char *playText = "play";
const char *mediaLeaderTitle = "Media";
const char *mediaPlayerLeaderTitle = "Media Player";
const char *restartText = "restart";
const char *currentTimeLabel = "00:00:01/00:00:06";
const char *timelineLeaderTitle = "Timeline";
const char *hideButtonLabel = "hide";
const char *setButtonLabel = "set";

Rectangle ScrollPanel015ScrollView = {0, 0, 0, 0};
Vector2 ScrollPanel015ScrollOffset = {0, 0};
Vector2 ScrollPanel015BoundsOffset = {0, 0};
Rectangle ScrollPanel019ScrollView = {0, 0, 0, 0};
Vector2 ScrollPanel019ScrollOffset = {0, 0};
Vector2 ScrollPanel019BoundsOffset = {0, 0};

void noop(void) {}
void newLayout(void) {}
void loadLayout(void) {}
void downloadLayout(void) {}
void exportVideo(void) {}
void undoBtn(void) {}
void redoBtn(void) {}
void donateDialogBtn(void) {}
void infoDialogBtn(void) {}
void Button013(void) {}
// END OF NEW

void GuiSetup(void) {
  fileImport = LoadFileDialog((Rectangle){105, 80, 230, 25}, "Upload Media",
                              "IMPORT VIDEO", "DRAG & DROP THE VIDEO",
                              (Vector2){97, 112});
}

void DrawGui(void) {
  // char frameCountLabel[50];
  // snprintf(frameCountLabel, 50, "Frame count: %d\n", getCurrentFrameCount());
  // GuiLabel((Rectangle){328, 448, 136, 32}, frameCountLabel);

  // START OF NEW
  if (GuiButton((Rectangle){16, 16, 24, 24}, newBtnText))
    newLayout();
  if (GuiButton((Rectangle){48, 16, 24, 24}, loadLayoutBtnText))
    loadLayout();
  if (GuiButton((Rectangle){80, 16, 24, 24}, downloadLayoutBtnText))
    downloadLayout();
  if (GuiButton((Rectangle){112, 16, 24, 24}, exportVideoBtnText))
    exportVideo();
  if (GuiButton((Rectangle){168, 16, 24, 24}, undoText))
    undoBtn();
  if (GuiButton((Rectangle){200, 16, 24, 24}, redoText))
    redoBtn();
  if (GuiButton((Rectangle){1064, 16, 24, 24}, donateText))
    donateDialogBtn();
  if (GuiButton((Rectangle){1032, 16, 24, 24}, infoText))
    infoDialogBtn();
  if (GuiButton((Rectangle){568, 392, 72, 24}, infoText))
    Button013();

  GuiGroupBox((Rectangle){96, 72, 248, 336}, mediaLeaderTitle);
  GuiScrollPanel((Rectangle){96, 112, 248 - ScrollPanel015BoundsOffset.x,
                             296 - ScrollPanel015BoundsOffset.y},
                 "", (Rectangle){0, 0, 0, 0}, &ScrollPanel015ScrollOffset,
                 &ScrollPanel015ScrollView);
  GuiGroupBox((Rectangle){376, 72, 544, 360}, mediaPlayerLeaderTitle);
  if (GuiButton((Rectangle){664, 392, 72, 24}, restartText))
    RestartVideo();
  GuiLabel((Rectangle){392, 392, 128, 24}, currentTimeLabel);
  GuiGroupBox((Rectangle){376, 464, 728, 248}, timelineLeaderTitle);
  GuiScrollPanel((Rectangle){440, 472, 656 - ScrollPanel019BoundsOffset.x,
                             232 - ScrollPanel019BoundsOffset.y},
                 "", (Rectangle){440, 472, 656, 232},
                 &ScrollPanel019ScrollOffset, &ScrollPanel019ScrollView);
  if (GuiButton((Rectangle){384, 480, 48, 16}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){384, 504, 48, 16}, setButtonLabel))
    noop();
  if (GuiButton((Rectangle){384, 536, 48, 16}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){384, 592, 48, 16}, setButtonLabel))
    noop();
  if (GuiButton((Rectangle){384, 648, 48, 16}, setButtonLabel))
    noop();
  if (GuiButton((Rectangle){384, 560, 48, 16}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){384, 616, 48, 16}, setButtonLabel))
    noop();
  if (GuiButton((Rectangle){384, 672, 48, 16}, hideButtonLabel))
    noop();
  // END OF NEW

  DrawFileDialog(fileImport);
  GuiInput();
}

static void GuiInput() {
  if (restartButton) {
    RestartVideo();
  }
  if (saveButton) {
    RestartVideo();
    // open a dialog, select sthe start and end
    // jump to framecount and wait until the duration * fps
    // open ffmpeg listening stdin
  }
}

void UnloadGui() { UnloadFileDialog(fileImport); }
