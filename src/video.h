#ifndef VIDEO_H
#define VIDEO_H

#include <stdbool.h>

bool initVideo(const char *filename);
void updateVideo(void);
void drawVideo(void);
void unloadVideo(void);
void restartVideo(void);
int getCurrentFrameCount(void);

#endif
