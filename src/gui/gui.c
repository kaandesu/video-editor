#include "gui.h"
#include "file_dialog.h"
#include "media_pool.h"
#include "menu_bar.h"
#include "raygui.h"
#include "raylib.h"
#include "timeline.h"

MediaPoolWindow *mpw;
void GuiSetup(void) {
  FileDialog *fileImport = LoadFileDialog(
      (Rectangle){105, 80, 230, 25}, "Upload Media", "IMPORT VIDEO",
      "DRAG & DROP THE VIDEO", (Vector2){97, 112});

  mpw = LoadMediaPoolWindow(fileImport);
}

void DrawGui(void) {
  /* Media Pool */
  DrawMediaPoolWindow(mpw);

  /* Timeline */
  DrawTimeline();

  /* Menu Bar */
  DrawMenuBar();
}

void UnloadGui() { UnloadMediaPoolWindow(mpw); }
