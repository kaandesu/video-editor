#include "raygui.h"
#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

typedef struct file_dialog FileDialog;

FileDialog *LoadFileDialog(Rectangle rect, const char *label,
                           const char *windowTitle, char *windowDesc,
                           Vector2 pos);

void DrawFileDialog(FileDialog *);
void UnloadFileDialog(FileDialog *);
FilePathList GetFilePathList(FileDialog *fd);
bool ShouldSavePaths(FileDialog *fd);
void savedPathsToPool(FileDialog *fd);

#endif
