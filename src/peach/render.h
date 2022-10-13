#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

namespace peach
{
    class Render
    {
    public:
        Render(const Render&)            = delete;
        Render& operator=(const Render&) = delete;

        static GLFWwindow* CreateWindow(int width, int height, const char* title)
        {
            auto ret = glfwInit();
            if (ret != GLFW_TRUE)
            {
                std::cout << "glfw init failed" << std::endl;
                return nullptr;
            }
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
            GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
            if (window == nullptr)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return nullptr;
            }
            glfwSetFramebufferSizeCallback(window, Render::FrameBufferSizeCallback);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, Render::MouseMoveCallback);
            glfwSetScrollCallback(window, Render::MouseScrollCallback);

            glfwMakeContextCurrent(window);
            if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
            {
                std::cout << "failed to init glad" << std::endl;
                glfwTerminate();
                return nullptr;
            }
            glEnable(GL_DEPTH_TEST);
            return window;
        }

        static GLuint CreateVAO()
        {
            unsigned int vao;
            glGenVertexArrays(1, &vao);
        }

        static void BindVAO(GLuint vao) { glBindVertexArray(vao); }

        static unsigned int CreateVBOUV(float* vertices, std::size_t length)
        {
            unsigned int vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, length, vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(
                1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

    private:
        static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            (void)window;
            glViewport(0, 0, width, height);
        }

        static void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
        {
            (void)window;
            if (first_mouse_)
            {
                last_xpos_   = xpos;
                last_ypos_   = ypos;
                first_mouse_ = false;
            }
            float xoffset = xpos - last_xpos_;
            float yoffset = ypos - last_ypos_;
            last_xpos_    = xpos;
            last_ypos_    = ypos;

            static const float SENSITIVITY = 0.05f;
            yaw_ += xoffset * SENSITIVITY;
            pitch_ += yoffset * SENSITIVITY;

            pitch_ = std::min(std::max(pitch_, -89.0f), 89.0f);

            float x       = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
            float y       = sin(glm::radians(pitch_));
            float z       = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
            camera_front_ = glm::normalize(glm::vec3(x, y, z));
        }

        static void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
        {
            (void)window;
            (void)xoffset;
            if (fov_ >= 1.0f && fov_ <= 45.0f)
            {
                fov_ -= yoffset;
            }
            fov_ = std::min(std::max(fov_, 1.0f), 45.0f);
        }

        static inline bool      first_mouse_  = false;
        static inline float     last_xpos_    = 0.0f;
        static inline float     last_ypos_    = 0.0f;
        static inline float     yaw_          = 0.0f;
        static inline float     pitch_        = 0.0f;
        static inline float     fov_          = 45.0f;
        static inline glm::vec3 camera_pos_   = glm::vec3(0.0f, 0.0f, 3.0f);
        static inline glm::vec3 camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
        static inline glm::vec3 camera_up_    = glm::vec3(0.0f, 1.0f, 0.0f);
    };
} // namespace peach