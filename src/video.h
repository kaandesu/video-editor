#ifndef VIDEO_H
#define VIDEO_H

#include <stdbool.h>

void LoadVideo(const char *filename);
void RenderVideo(void);
void DrawVideo(void);
void renderVideo(void);
void UnloadVideo(void);
void restartVideo(void);
int getCurrentFrameCount(void);
char *getFilePath(void);
void updateFilePath(const char *filename);

#endif
