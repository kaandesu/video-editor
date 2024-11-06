#include "gui.h"
#include "file_dialog.h"
#include "menu_bar.h"
#include "raygui.h"
#include "raylib.h"
#include "style.h"
#include "video.h"
#include <time.h>

/* Titles */
#define MediaPoolTitle "Media"
#define MediaPLayerTitle "Media Player"
#define TimelineTitle "Timeline"

/* shared offsets */
#define X_OFFSET1 376

static float duration = 5.0f;

static bool uploadButton = false;
static bool saveButton = false;
static FileDialog *fileImport;

// NEW

const char *playText = "#131#";
const char *hideButtonLabel = "#44#";
const char *muteButtonLabel = "#122#";

const char *currentTimeLabel = "00:00:01/00:00:06";

Rectangle mediaSourcesAreaScrollView = {0, 0, 0, 0};
Vector2 mediaSourcesAreaScrollOffset = {0, 0};
Vector2 mediaSourcesAreaOffset = {0, 0};

Rectangle ScrollPanel019ScrollView = {0, 0, 0, 0};
Vector2 ScrollPanel019ScrollOffset = {0, 0};
Vector2 ScrollPanel019BoundsOffset = {0, 0};
// END OF NEW

static void noop(void) {}

void GuiSetup(void) {
  fileImport = LoadFileDialog((Rectangle){105, 80, 230, 25}, "Upload Media",
                              "IMPORT VIDEO", "DRAG & DROP THE VIDEO",
                              (Vector2){97, 112});
}

void DrawGui(void) {

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

  GuiGroupBox((Rectangle){X_OFFSET1, 72, 544, 360}, MediaPLayerTitle);
  if (GuiButton((Rectangle){600, 392, MD, SM}, playText))
    RestartVideo();
  if (GuiButton((Rectangle){664, 392, MD, SM}, ICON_RESTART))
    RestartVideo();
  GuiLabel((Rectangle){392, 392, 128, 24}, currentTimeLabel);

  /* Timeline scrollpanel */
  GuiGroupBox((Rectangle){X_OFFSET1, 464, 728, 248}, TimelineTitle);
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
  if (GuiButton((Rectangle){X_OFFSET1 + 8, 504, LG, XS}, ICON_GEAR))
    noop();

  if (GuiButton((Rectangle){X_OFFSET1 + 8, 536, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8 + XS + 8, 536, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8, 560, LG, XS}, ICON_GEAR))
    noop();

  if (GuiButton((Rectangle){X_OFFSET1 + 8, 592, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8 + XS + 8, 592, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8, 616, LG, XS}, ICON_GEAR))
    noop();

  if (GuiButton((Rectangle){X_OFFSET1 + 8, 648, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8 + XS + 8, 648, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET1 + 8, 672, LG, XS}, ICON_GEAR))
    noop();

  /* End of Timeline buttons */
}

void UnloadGui() { UnloadFileDialog(fileImport); }
