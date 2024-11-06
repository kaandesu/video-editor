#include "timeline.h"
#include "raygui.h"
#include "raylib.h"
#include "style.h"
#include <stdlib.h>

#define X_OFFSET 376
#define TimelineTitle "Timeline"

const char *hideButtonLabel = ICON_EYE_ON;
const char *muteButtonLabel = ICON_AUDIO;

Rectangle ScrollPanel019ScrollView = {0, 0, 0, 0};
Vector2 ScrollPanel019ScrollOffset = {0, 0};
Vector2 ScrollPanel019BoundsOffset = {0, 0};

static void noop(void) {}

void DrawTimeline() {

  /* Timeline scrollpanel */
  GuiGroupBox((Rectangle){X_OFFSET, 464, 728, 248}, TimelineTitle);
  GuiScrollPanel((Rectangle){440, 472, 656 - ScrollPanel019BoundsOffset.x,
                             232 - ScrollPanel019BoundsOffset.y},
                 NULL, (Rectangle){440, 472, 656, 232},
                 &ScrollPanel019ScrollOffset, &ScrollPanel019ScrollView);
  /* End of Timeline scrollpanel */

  /* Timeline buttons */
  if (GuiButton((Rectangle){X_OFFSET + 8, 480, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET + 8 + XS + 8, 480, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET + 8, 504, LG, XS}, ICON_GEAR))
    noop();

  if (GuiButton((Rectangle){X_OFFSET + 8, 536, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET + 8 + XS + 8, 536, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET + 8, 560, LG, XS}, ICON_GEAR))
    noop();

  if (GuiButton((Rectangle){X_OFFSET + 8, 592, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET + 8 + XS + 8, 592, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET + 8, 616, LG, XS}, ICON_GEAR))
    noop();

  if (GuiButton((Rectangle){X_OFFSET + 8, 648, XS, XS}, hideButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET + 8 + XS + 8, 648, XS, XS},
                muteButtonLabel))
    noop();
  if (GuiButton((Rectangle){X_OFFSET + 8, 672, LG, XS}, ICON_GEAR))
    noop();
}
