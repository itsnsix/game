set(SOURCE
        ${CMAKE_SOURCE_DIR}/src/obj/loadObj/loadObj.c
        ${CMAKE_SOURCE_DIR}/src/obj/utils/objUtils.c)

set(HEADERS
        ${CMAKE_SOURCE_DIR}/src/obj/loadObj/loadObj.h
        ${CMAKE_SOURCE_DIR}/src/obj/utils/objUtils.h)

include_directories(
        ${CMAKE_SOURCE_DIR}/src/utils/loadFile
        ${CMAKE_SOURCE_DIR}/src/obj/types
        ${CMAKE_SOURCE_DIR}/src/obj/loadObj
        ${CMAKE_SOURCE_DIR}/src/obj/utils
        ${CMAKE_SOURCE_DIR}/src/testUtils)

add_library(obj ${SOURCE})
target_link_libraries(obj utils)


add_executable(objUtils.test.bin ./utils/objUtils.test.c)
target_link_libraries(objUtils.test.bin obj)
set_target_properties(objUtils.test.bin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/testbin)

add_executable(loadObj.test.bin ./loadObj/loadObj.test.c)
target_link_libraries(loadObj.test.bin obj utils)
target_compile_definitions(loadObj.test.bin PUBLIC DATA_DIR="${CMAKE_SOURCE_DIR}/data/")
