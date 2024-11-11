#include "menu_bar.h"
#include "raygui.h"
#include "raylib.h"
#include "style.h"
#include "video.h"
#include <stdlib.h>

bool recording = false;

static void noop(void) {}
void newLayout(void) {}
void loadLayout(void) {}
void downloadLayout(void) {}
void exportVideo(void) {
  recording = !recording;
  if (recording) {
    StartRecording();
  } else {
    StopRecording();
  }
}
void undoBtn(void) {}
void redoBtn(void) {}
void donateDialogBtn(void) {}
void infoDialogBtn(void) {}

void DrawMenuBar() {
  GuiPanel((Rectangle){152, -1, 88, MD + 6}, NULL);
  GuiPanel((Rectangle){GetScreenWidth() - 83, -1, 88, MD + 6}, NULL);
  GuiLine((Rectangle){0, P_MD + 4, GetScreenWidth(), 0}, "Options");

  if (GuiButton((Rectangle){16, P_XXS, SM, SM}, ICON_FILE_ADD))
    newLayout();
  if (GuiButton((Rectangle){48, P_XXS, SM, SM}, ICON_FILE_OPEN))
    loadLayout();
  if (GuiButton((Rectangle){80, P_XXS, SM, SM}, ICON_FILE_SAVE))
    downloadLayout();
  if (GuiButton((Rectangle){112, P_XXS, SM, SM}, ICON_FILE_EXPORT))
    exportVideo();
  if (GuiButton((Rectangle){168, P_XXS, SM, SM}, ICON_UNDO_FILL))
    undoBtn();
  if (GuiButton((Rectangle){200, P_XXS, SM, SM}, ICON_REDO_FILL))
    redoBtn();
  if (GuiButton((Rectangle){1032, P_XXS, SM, SM}, ICON_HEART))
    donateDialogBtn();
  if (GuiButton((Rectangle){1064, P_XXS, SM, SM}, ICON_INFO_BOX))
    infoDialogBtn();
}
