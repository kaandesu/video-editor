## video-editor

Creating my own basic video-editor in raylib, using ffmpeg and libmpeg2.

<div align="center">
  <img width="520" src="./data/demo.gif">
</div>

> [!IMPORTANT]
> video-editor is currently under development. Gif above is from a 1-2 hours of work,
> probably doesn't reflect the current progress. Will update on every minor version update.

Tasks:

- Layout design with raygui
- Upload .mpg files
- Adding and stiching existing video and decoding with libmpeg2
- Saving the editor state, so you don't lose progress after restart
- Saving the final result with ffmpeg
- Simple manim like animation pipeline through configuration files