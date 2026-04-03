// clang-format off
#include "shader.hpp"
#include <cmath>
// #include <GLES3/gl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// clang-format on
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

void processInput(GLFWwindow *window);

// we only need this vertex because we need to pass the position from the vertex
// to the another graphic pipeline step

int main() {
        std::cout << "DEBUG: Initializing C++ program" << "\n";

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window;

        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                                  "learnopengl.com", NULL, NULL);

        glfwMakeContextCurrent(window);
        // TODO: listen for possible resizes
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "ERROR: failed to load glad library" << "\n";

                return -1;
        }

        // clang-format off
        float vertices[] = {
            // Denote that always you have to respect the order of the vertices
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        };
        // clang-format on

        unsigned int VAO, VBO;

        // i don't understand the VAO at all
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void *)0);

        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                              (void *)(3 * sizeof(float)));

        glEnableVertexAttribArray(1);

        // i think this is for free memory
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        Shader ourShader("../shaders/triangle.vert",
                         "../shaders/triangle.frag");

        while (!glfwWindowShouldClose(window)) {
                processInput(window);

                // rendering commands here
                // this sets the color that will be used by
                // `glClear`
                glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
                glClear(GL_COLOR_BUFFER_BIT);

                float time = glfwGetTime();

                ourShader.use();
                // ourShader.setFloat("xOffset", 0.0f);

                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                glfwPollEvents();
                glfwSwapBuffers(window);
        }

        return 0;
}

void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, 1);
        }
}
