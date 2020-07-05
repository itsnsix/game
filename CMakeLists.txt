cmake_minimum_required(VERSION 3.10)
project(racing-game)

add_executable(racing-game main.c)

if (MINGW)
    link_directories(C:\\MinGW\\lib)
    include_directories(C:\\MinGW\\include)
    target_link_libraries(racing-game mingw32 SDL2main SDL2 glew32 opengl32)
else()
    target_link_libraries(racing-game SDL2 SDL2main GLEW GL)
endif(MINGW)

add_subdirectory(src/obj)