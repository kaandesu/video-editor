#ifndef VIDEO_H
#define VIDEO_H

#include <stdbool.h>

void LoadVideo(const char *filename);
void RenderVideo(void);
void DrawVideo(void);
void UnloadVideo(void);
void RestartVideo(void);
int getCurrentFrameCount(void);
char *GetFilePath(void);
void UpdateFilePath(const char *filename);
void StartRecording();
void StopRecording();

#endif
