#include "gui.h"
#include "file_dialog.h"
#include "menu_bar.h"
#include "raygui.h"
#include "raylib.h"
#include "style.h"
#include "timeline.h"
#include "video.h"
#include <time.h>

/* Titles */
#define MediaPoolTitle "Media"
#define MediaPLayerTitle "Media Player"

#define X_OFFSET 376

static bool uploadButton = false;
static bool saveButton = false;
static FileDialog *fileImport;

const char *playText = ICON_PLAYER_PLAY;
const char *currentTimeLabel = "00:00:00/00:00:00";

Rectangle mediaSourcesAreaScrollView = {0, 0, 0, 0};
Vector2 mediaSourcesAreaScrollOffset = {0, 0};
Vector2 mediaSourcesAreaOffset = {0, 0};

static void noop(void) {}

void GuiSetup(void) {
  fileImport = LoadFileDialog((Rectangle){105, 80, 230, 25}, "Upload Media",
                              "IMPORT VIDEO", "DRAG & DROP THE VIDEO",
                              (Vector2){97, 112});
}

void DrawGui(void) {
  /* Timeline */
  DrawTimeline();

  /* Menu Bar */
  DrawMenuBar();

  /* Media Source Pane  */
  GuiGroupBox((Rectangle){96, 72, 248, 336}, MediaPoolTitle);
  GuiScrollPanel((Rectangle){96, 112, 248 - mediaSourcesAreaOffset.x,
                             296 - mediaSourcesAreaOffset.y},
                 NULL, (Rectangle){96, 112, 248, 296},
                 &mediaSourcesAreaScrollOffset, &mediaSourcesAreaScrollView);

  DrawFileDialog(fileImport);
  /* End of Media Source Pane  */

  GuiGroupBox((Rectangle){X_OFFSET, 72, 544, 360}, MediaPLayerTitle);
  if (GuiButton((Rectangle){600, 392, MD, SM}, playText))
    RestartVideo();
  if (GuiButton((Rectangle){664, 392, MD, SM}, ICON_RESTART))
    RestartVideo();
  GuiLabel((Rectangle){392, 392, 128, 24}, currentTimeLabel);

  /* End of Timeline buttons */
}

void UnloadGui() { UnloadFileDialog(fileImport); }
