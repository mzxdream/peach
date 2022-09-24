set(TARGET_NAME peach)

file(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(${TARGET_NAME} ${SRC_LIST})

find_package(OpenGL REQUIRED)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(${TARGET_NAME} PUBLIC ${PEACH_THIRD_PARTY_DIR}/glfw/include)

target_link_libraries(${TARGET_NAME} PUBLIC glfw)
target_link_libraries(${TARGET_NAME} PRIVATE OpenGL::GL)

message(STATUS "Generating install")
install(
    TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})