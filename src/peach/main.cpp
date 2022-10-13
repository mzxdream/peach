#include <iostream>
#include <peach/data.h>
#include <peach/render.h>
#include <peach/shader.h>

static constexpr unsigned int SCR_WIDTH  = 800;
static constexpr unsigned int SCR_HEIGHT = 600;

int main(int, char*[])
{
    GLFWwindow* window = peach::Render::CreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    GLuint vao  = peach::Render::CreateVAO();
    GLuint vbo  = peach::Render::CreateVBOUV(peach::VERTICES, sizeof(peach::VERTICES));
    GLuint tex1 = peach::Render::CreateTexture2D("resources/textures/container.jpg", GL_RGB);
    GLuint tex2 = peach::Render::CreateTexture2D("resources/textures/awesomeface.png", GL_RGBA);

    Shader shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    while (!glfwWindowShouldClose(window))
    {
        peach::Render::ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex2);
        // activate shader
        shader.use();
        // camera/view transformation
        glm::mat4 view = peach::Render::GetView();
        shader.setMat4("view", view);
        glm::mat4 projection = peach::Render::GetProjection(static_cast<float>(SCR_WIDTH) / SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);
        // render boxes
        glBindVertexArray(vao);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model           = glm::translate(model, peach::CUBE_POSITIONS[i]);
            float angle     = 20.0f * i;
            model           = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}