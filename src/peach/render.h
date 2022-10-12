#pragma once

#include <GLFW/glfw3.h>

#include <iostream>

class Render
{
public:
    Render(const Render&)            = delete;
    Render& operator=(const Render&) = delete;

    bool Init(int width, int height, const char* title)
    {
        auto ret = glfwInit();
        if (ret != GLFW_TRUE)
        {
            std::cout << "glfw init failed" << std::endl;
            return false;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window_ == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        glfwSetFramebufferSizeCallback(window_, Render::FrameBufferSizeCallback);
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window_, Render::MouseMoveCallback);
        // glfwSetScrollCallback(m_window, Render::mouseScrollCallback);

        glfwMakeContextCurrent(window_);

        glEnable(GL_DEPTH_TEST);
        return true;
    }
    void Clear() {}

private:
    static void FrameBufferSizeCallback(GLFWwindow*, int width, int height) { glViewport(0, 0, width, height); }
    static void MouseMoveCallback(GLFWwindow*, double xpos, double ypos) {}

    static double last_xpos;
    static double last_ypos;

public:
    GLFWwindow* window_;
};