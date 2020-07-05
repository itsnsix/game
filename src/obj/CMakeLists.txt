set(SOURCE
        ./loadObj/loadObj.c
        ./utils/objUtils.c)

set(HEADERS
        ./loadObj/loadObj.h
        ./utils/objUtils.h)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/obj/types
        ${CMAKE_SOURCE_DIR}/src/obj/loadObj
        ${CMAKE_SOURCE_DIR}/src/obj/utils
        ${CMAKE_SOURCE_DIR}/src/testUtils)

add_library(obj ${SOURCE})


add_executable(objUtils.test.bin ./utils/objUtils.test.c)
target_link_libraries(objUtils.test.bin obj)
set_target_properties(objUtils.test.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)

add_executable(loadObj.test.bin ./loadObj/loadObj.test.c)
target_link_libraries(loadObj.test.bin obj)
set_target_properties(loadObj.test.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)
target_compile_definitions(loadObj.test.bin PUBLIC TRIANGLE_OBJ_FILE_PATH="${CMAKE_SOURCE_DIR}/triangle.obj")