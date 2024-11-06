#include "file_dialog.h"

#ifndef MEDIA_POOL_H
#define MEDIA_POOL_H

typedef struct media_pool_window MediaPoolWindow;

void UnloadMediaPoolWindow(MediaPoolWindow *mpw);
MediaPoolWindow *LoadMediaPoolWindow(FileDialog *fd);
void DrawMediaPoolWindow(MediaPoolWindow *mpw);

#endif
