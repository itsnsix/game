set(SOURCE
        ./loadObj/loadObj.c
        ./utils/objUtils.c)

set(HEADERS
        ./loadObj/loadObj.h)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/obj/types
        ${CMAKE_SOURCE_DIR}/src/testUtils)

add_library(obj ${SOURCE})


add_executable(objUtils.test.bin ./utils/objUtils.test.c)
target_link_libraries(objUtils.test.bin obj)
set_target_properties(objUtils.test.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)

