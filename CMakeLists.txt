cmake_minimum_required(VERSION 3.0)
project(MyProject C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Paths
set(pwd ${CMAKE_CURRENT_SOURCE_DIR})
set(RAYLIB_DIR ${pwd}/lib/raylib)
set(MPEG2_DIR ${pwd}/lib/libmpeg2)
set(src ${pwd}/src)
set(gui ${src}/gui)
set(style ${pwd}/styles/cyber)

include_directories(
    ${RAYLIB_DIR}/include
    ${MPEG2_DIR}/include
    ${style}
    ${src}
    ${gui}
)

add_executable(video_editor
    ${src}/main.c
    ${src}/video.c
    ${src}/input.c
    ${gui}/gui.c
    ${gui}/file_dialog.c
    ${gui}/menu_bar.c
    ${gui}/timeline.c
    ${gui}/media_pool.c
    ${gui}/media_control.c
)

target_link_libraries(video_editor
    ${RAYLIB_DIR}/lib/libraylib.a
    ${MPEG2_DIR}/lib/libmpeg2.a
    ${MPEG2_DIR}/lib/libmpeg2convert.a
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
)
