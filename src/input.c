#include "raylib.h"
#include "video.h"

void listenInput() {
  if (IsKeyDown(KEY_R)) {
    restartVideo();
  }
}
