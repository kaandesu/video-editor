#include "gui.h"
#include "file_dialog.h"
#include "raygui.h"
#include "raylib.h"
#include "style.h"
#include "video.h"
#include <time.h>

/* shared offsets */
#define X_OFFSET1 376

static float duration = 5.0f;

static bool uploadButton = false;
static bool restartButton = false;
static bool saveButton = false;
static FileDialog *fileImport;
static void GuiInput();

// NEW
const char *newBtnText = "#8#";
const char *loadLayoutBtnText = "#5#";
const char *downloadLayoutBtnText = "#6#";
const char *exportVideoBtnText = "#7#";
const char *undoText = "#72#";
const char *redoText = "#73#";
const char *donateText = "#191#";
const char *infoText = "#186#";
const char *playText = "#131#";
const char *restartText = "#211#";
const char *mediaLeaderTitle = "Media";
const char *mediaPlayerLeaderTitle = "Media Player";
const char *currentTimeLabel = "00:00:01/00:00:06";
const char *timelineLeaderTitle = "Timeline";
const char *hideButtonLabel = "#44#";
const char *muteButtonLabel = "#122#";
const char *setButtonLabel = "#141#";

Rectangle mediaSourcesAreaScrollView = {0, 0, 0, 0};
Vector2 mediaSourcesAreaScrollOffset = {0, 0};
Vector2 mediaSourcesAreaOffset = {0, 0};

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

  /* Top bar */
  GuiLine((Rectangle){0, P_MD + 4, GetScreenWidth(), 0}, "Options");
  GuiPanel((Rectangle){152, 0, 88, MD + 5}, NULL);
  GuiPanel((Rectangle){GetScreenWidth() - 83, 0, 88, MD + 5}, NULL);

  if (GuiButton((Rectangle){16, P_XXS, SM, SM}, newBtnText))
    newLayout();
  if (GuiButton((Rectangle){48, P_XXS, SM, SM}, loadLayoutBtnText))
    loadLayout();
  if (GuiButton((Rectangle){80, P_XXS, SM, SM}, downloadLayoutBtnText))
    downloadLayout();
  if (GuiButton((Rectangle){112, P_XXS, SM, SM}, exportVideoBtnText))
    exportVideo();
  if (GuiButton((Rectangle){168, P_XXS, SM, SM}, undoText))
    undoBtn();
  if (GuiButton((Rectangle){200, P_XXS, SM, SM}, redoText))
    redoBtn();
  if (GuiButton((Rectangle){1032, P_XXS, SM, SM}, donateText))
    donateDialogBtn();
  if (GuiButton((Rectangle){1064, P_XXS, SM, SM}, infoText))
    infoDialogBtn();

  /* End of Top bar */

  /* Media Source Pane  */
  GuiGroupBox((Rectangle){96, 72, 248, 336}, mediaLeaderTitle);
  GuiScrollPanel((Rectangle){96, 112, 248 - mediaSourcesAreaOffset.x,
                             296 - mediaSourcesAreaOffset.y},
                 NULL, (Rectangle){96, 112, 248, 296},
                 &mediaSourcesAreaScrollOffset, &mediaSourcesAreaScrollView);

  DrawFileDialog(fileImport);
  /* End of Media Source Pane  */

  GuiGroupBox((Rectangle){X_OFFSET1, 72, 544, 360}, mediaPlayerLeaderTitle);
  if (GuiButton((Rectangle){600, 392, MD, SM}, playText))
    RestartVideo();
  if (GuiButton((Rectangle){664, 392, MD, SM}, restartText))
    RestartVideo();
  GuiLabel((Rectangle){392, 392, 128, 24}, currentTimeLabel);

  /* Timeline scrollpanel */
  GuiGroupBox((Rectangle){X_OFFSET1, 464, 728, 248}, timelineLeaderTitle);
  GuiScrollPanel((Rectangle){440, 472, 656 - ScrollPanel019BoundsOffset.x,
                             232 - ScrollPanel019BoundsOffset.y},
                 NULL, (Rectangle){440, 472, 656, 232},
                 &ScrollPanel019ScrollOffset, &ScrollPanel019ScrollView);

  /* End of Timeline scrollpanel */

  /* Timeline buttons */

  if (GuiButton((Rectangle){X_OFFSET1 + 8, 480, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8 + XS + 8, 480, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8, 504, LG, XS}, setButtonLabel))
    noop();

  if (GuiButton((Rectangle){X_OFFSET1 + 8, 536, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8 + XS + 8, 536, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8, 560, LG, XS}, setButtonLabel))
    noop();

  if (GuiButton((Rectangle){X_OFFSET1 + 8, 592, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8 + XS + 8, 592, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8, 616, LG, XS}, setButtonLabel))
    noop();

  if (GuiButton((Rectangle){X_OFFSET1 + 8, 648, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8 + XS + 8, 648, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8, 672, LG, XS}, setButtonLabel))
    noop();

  /* End of Timeline buttons */

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
