#include "media_control.h"
#include "raygui.h"
#include "raylib.h"
#include "style.h"
#include "video.h"

#define X_OFFSET 376
#define MediaPLayerTitle "Media Control"

const char *TEMPcurrentTimeLabel = "00:00:00/00:00:00";

// TODO: associate media_control with the video
// so that it would be possible to create multiple if wanted

void DrawMediaControl() {
  GuiGroupBox((Rectangle){X_OFFSET, 72, 544, 360}, MediaPLayerTitle);
  if (GuiButton((Rectangle){600, 392, MD, SM}, ICON_PLAYER_PLAY))
    RestartVideo();
  if (GuiButton((Rectangle){664, 392, MD, SM}, ICON_RESTART))
    RestartVideo();
  GuiLabel((Rectangle){392, 392, 128, 24}, TEMPcurrentTimeLabel);
}
