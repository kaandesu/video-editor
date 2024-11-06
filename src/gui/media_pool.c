#include "media_pool.h"
#include "file_dialog.h"
#include "raylib.h"
#include "style.h"
#include "video.h"
#include <stdlib.h>
#include <time.h>

#define X_OFFSET 376

#define MediaPoolTitle "Media"
#define MediaPLayerTitle "Media Player"

const char *playText = ICON_PLAYER_PLAY;
const char *currentTimeLabel = "00:00:00/00:00:00";

Rectangle mediaSourcesAreaScrollView = {0, 0, 0, 0};
Vector2 mediaSourcesAreaScrollOffset = {0, 0};
Vector2 mediaSourcesAreaOffset = {0, 0};

typedef struct media_pool_window {
  FileDialog *fd;
} MediaPoolWindow;

static void noop(void) {}
void DrawMediaPoolWindow(MediaPoolWindow *mpw) {

  /* Media Source Pane  */
  GuiGroupBox((Rectangle){96, 72, 248, 336}, MediaPoolTitle);
  GuiScrollPanel((Rectangle){96, 112, 248 - mediaSourcesAreaOffset.x,
                             296 - mediaSourcesAreaOffset.y},
                 NULL, (Rectangle){96, 112, 248, 296},
                 &mediaSourcesAreaScrollOffset, &mediaSourcesAreaScrollView);

  DrawFileDialog(mpw->fd);
  /* End of Media Source Pane  */

  GuiGroupBox((Rectangle){X_OFFSET, 72, 544, 360}, MediaPLayerTitle);
  if (GuiButton((Rectangle){600, 392, MD, SM}, playText))
    RestartVideo();
  if (GuiButton((Rectangle){664, 392, MD, SM}, ICON_RESTART))
    RestartVideo();
  GuiLabel((Rectangle){392, 392, 128, 24}, currentTimeLabel);
}

MediaPoolWindow *LoadMediaPoolWindow(FileDialog *fd) {
  MediaPoolWindow *mpw = (MediaPoolWindow *)malloc(sizeof(MediaPoolWindow));
  if (mpw == NULL) {
    TraceLog(LOG_ERROR, "could not allocate MediaPoolWindow");
    exit(EXIT_FAILURE);
  }
  mpw->fd = fd;

  return mpw;
}

void UnloadMediaPoolWindow(MediaPoolWindow *mpw) {
  if (mpw == NULL)
    return;

  if (mpw->fd != NULL) {
    UnloadFileDialog(mpw->fd);
    mpw->fd = NULL;
  }

  free(mpw);
}
