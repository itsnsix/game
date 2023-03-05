set(SOURCE
        ./utils/glslUtils.c)

set(HEADERS
        ./utils/glslUtils.h)


include_directories(
        ${CMAKE_SOURCE_DIR}/src/utils/loadFile
        ${CMAKE_SOURCE_DIR}/src/glsl/utils
        ${CMAKE_SOURCE_DIR}/src/testUtils)

add_library(glsl ${SOURCE})
target_link_libraries(glsl utils)

if (MINGW)
    target_link_libraries(glsl glew32 opengl32)
else ()
    target_link_libraries(glsl GLEW GL)
endif(MINGW)


add_executable(glslUtils.test.bin ./utils/glslUtils.test.c)
target_link_libraries(glslUtils.test.bin obj utils)