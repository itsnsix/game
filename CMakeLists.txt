cmake_minimum_required(VERSION 3.10)
project(game)

add_executable(game main.c)
include_directories(
        ${CMAKE_SOURCE_DIR}/src/obj/inc
        ${CMAKE_SOURCE_DIR}/src/obj/types
        ${CMAKE_SOURCE_DIR}/src/obj/utils
        ${CMAKE_SOURCE_DIR}/src/utils/loadFile
        ${CMAKE_SOURCE_DIR}/src/testUtils)

if (MINGW)
    link_directories(C:\\MinGW\\lib)
    include_directories(C:\\MinGW\\include)
    target_link_libraries(game mingw32 SDL2main SDL2 glew32 opengl32 obj glsl m)
else()
    target_link_libraries(game SDL2 SDL2main GLEW GL obj glsl m)
endif(MINGW)

add_subdirectory(src/obj)
add_subdirectory(src/glsl)
add_subdirectory(src/img)
add_subdirectory(src/utils)

target_compile_definitions(game PUBLIC DATA_DIR="${CMAKE_SOURCE_DIR}/data/")