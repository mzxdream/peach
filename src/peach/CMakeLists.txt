set(TARGET_NAME peach)

file(GLOB_RECURSE SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${TARGET_NAME} ${SRC_LIST} ${GLAD_SRC_LIST})

find_package(OpenGL REQUIRED)

target_compile_definitions(${TARGET_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)

target_include_directories(${TARGET_NAME} PRIVATE ${GLM_INC_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${GLAD_INC_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${GLFW_INC_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${PEACH_INC_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${THIRD_PARTY_INC_DIR})

target_link_libraries(${TARGET_NAME} PRIVATE glfw)
target_link_libraries(${TARGET_NAME} PRIVATE OpenGL::GL)

install(
    TARGETS ${TARGET_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})