set(SOURCE
        ${CMAKE_SOURCE_DIR}/src/utils/loadFile/loadFile.c
        ${CMAKE_SOURCE_DIR}/src/utils/byteSwap/byteSwap.c)

set(HEADERS
        ${CMAKE_SOURCE_DIR}/src/utils/loadFile/loadFile.h
        ${CMAKE_SOURCE_DIR}/src/utils/byteSwap/byteSwap.h)

add_library(utils ${SOURCE})

add_executable(loadFile.test.bin loadFile/loadFile.test.c)
add_executable(byteSwap.test.bin byteSwap/byteSwap.test.c)


