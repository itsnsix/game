set(SOURCE
        ${CMAKE_SOURCE_DIR}/src/img/loadImg/loadImg.c
        ${CMAKE_SOURCE_DIR}/src/img/loadImg/loadJpg/loadJpg.c
        ${CMAKE_SOURCE_DIR}/src/img/loadImg/loadPng/loadPng.c)

set(HEADERS
        ${CMAKE_SOURCE_DIR}/src/img/loadImg/loadImg.h
        ${CMAKE_SOURCE_DIR}/src/img/loadImg/loadJpg/loadJpg.h
        ${CMAKE_SOURCE_DIR}/src/img/loadPng/loadPng.h)

add_library(img ${SOURCE})
target_link_libraries(img utils)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/utils/loadFile/
        ${CMAKE_SOURCE_DIR}/src/utils/byteSwap/
        ${CMAKE_SOURCE_DIR}/src/img/loadImg/
        ${CMAKE_SOURCE_DIR}/src/img/loadImg/loadJpg
        ${CMAKE_SOURCE_DIR}/src/img/loadImg/loadPng
        ${CMAKE_SOURCE_DIR}/src/img/types
)

add_executable(loadImg.test.bin ./loadImg/loadImg.test.c)
target_link_libraries(loadImg.test.bin img)
set_target_properties(loadImg.test.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)

add_executable(loadJpg.test.bin ./loadImg/loadJpg/loadJpg.test.c)
target_link_libraries(loadJpg.test.bin img)
set_target_properties(loadJpg.test.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)

add_executable(loadPng.test.bin ./loadImg/loadPng/loadPng.test.c)
target_link_libraries(loadPng.test.bin img)
set_target_properties(loadPng.test.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)