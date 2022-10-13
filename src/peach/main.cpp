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
    // GLuint vao  = peach::Render::CreateVAO();
    // GLuint vbo  = peach::Render::CreateVBOUV(peach::VERTICES, sizeof(peach::VERTICES));
    // GLuint tex1 = peach::Render::CreateTexture2D("resources/textures/container.jpg", GL_RGB);
    // GLuint tex2 = peach::Render::CreateTexture2D("resources/textures/awesomeface.png", GL_RGBA);

    // Shader shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");
    // shader.use();
    // shader.setInt("texture1", 0);
    // shader.setInt("texture2", 1);

    GLuint vao_cube = peach::Render::CreateVAO();
    GLuint vbo_cube = peach::Render::CreateVBOUV(peach::VERTICES, sizeof(peach::VERTICES));
    (void)vbo_cube;
    Shader cube_shader("resources/shaders/cube_shader.vs", "resources/shaders/cube_shader.fs");
    cube_shader.use();
    cube_shader.setVec3("objColor", 1.0f, 0.5f, 0.31f);
    cube_shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

    //GLuint vao_light = peach::Render::CreateVAO();
    //GLuint vbo_light = peach::Render::CreateVBOUV(peach::VERTICES, sizeof(peach::VERTICES));
    //(void)vbo_light;
    glm::vec3 light_pos(1.2f, 1.0f, 2.0f);
    Shader    light_shader("resources/shaders/light_shader.vs", "resources/shaders/light_shader.fs");
    light_shader.use();

    while (!glfwWindowShouldClose(window))
    {
        peach::Render::ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view       = peach::Render::GetView();
        glm::mat4 projection = peach::Render::GetProjection(static_cast<float>(SCR_WIDTH) / SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 model      = glm::mat4(1.0f);
        // bind textures on corresponding texture units
        cube_shader.use();
        cube_shader.setMat4("view", view);
        cube_shader.setMat4("projection", projection);
        cube_shader.setMat4("model", model);
        glBindVertexArray(vao_cube);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // lamp
        light_shader.use();
        light_shader.setMat4("view", view);
        light_shader.setMat4("projection", projection);
        glm::mat4 light_model = glm::mat4(1.0f);
        light_model           = glm::translate(light_model, light_pos);
        light_model           = glm::scale(light_model, glm::vec3(0.2f));
        light_shader.setMat4("model", light_model);
        glBindVertexArray(vao_cube);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}