option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if(NOT TARGET glfw)
    option(GLFW_BUILD_EXAMPLES "" OFF)
    option(GLFW_BUILD_TESTS "" OFF)
    option(GLFW_BUILD_DOCS "" OFF)
    #option(GLFW_INSTALL "" OFF)
    add_subdirectory(glfw)
endif()