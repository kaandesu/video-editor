cmake_minimum_required(VERSION 3.0)
project(MyProject C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(RAYLIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib")
set(CYBER_STYLE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/styles/cyber")
set(GUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/gui")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(HOMEBREW_DIR "/opt/homebrew/include/")

find_package(PkgConfig REQUIRED)
pkg_check_modules(MPEGS REQUIRED libmpeg2)


include_directories(${RAYLIB_DIR}/include  ${HOMEBREW_DIR} ${CYBER_STYLE_DIR} ${GUI_DIR} ${SRC_DIR})
link_directories(${MPEGS_LIBRARY_DIRS})

add_executable(video_editor src/main.c src/video.c src/input.c src/gui/gui.c  src/gui/file_dialog.c src/gui/menu_bar.c)

if(APPLE)
    target_link_libraries(video_editor 
        "${RAYLIB_DIR}/libraylib.a" 
        ${MPEGS_LIBRARIES}
        "-lmpeg2convert"
        "-framework Cocoa" 
        "-framework OpenGL" 
        "-framework IOKit" 
        "-framework CoreVideo" 
        ${CMAKE_DL_LIBS} 
    )
else()
    target_link_libraries(video_editor
      "${RAYLIB_DIR}/libraylib.a"
      ${MPEGS_LIBRARIES}
      "-lmpeg2convert"
      ${CMAKE_DL_LIBS}
    )
endif()
