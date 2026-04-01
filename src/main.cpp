// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// clang-format on
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

void processInput(GLFWwindow *window);

// we only need this vertex because we need to pass the position from the vertex
// to the another graphic pipeline step
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n "
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n"
    "\0 ";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main() {\n "
                                   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n"
                                   "\0 ";

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

        unsigned int vertexShader;

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // Why there is a one? Don't ask to me
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        int success;
        char infoLog[256];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success) {
                glGetShaderInfoLog(vertexShader, 256, NULL, infoLog);

                std::cout << "ERROR COMPILATING SHADER: " << infoLog << '\n';
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // Why there is a one? Don't ask to me
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success) {
                glGetShaderInfoLog(fragmentShader, 256, NULL, infoLog);

                std::cout << "ERROR COMPILATING SHADER: " << infoLog << '\n';
        }

        unsigned int shaderProgram;

        shaderProgram = glCreateProgram();

        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        // TODO: check for errors here
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

        if (!success) {
                glGetProgramInfoLog(shaderProgram, 256, NULL, infoLog);

                std::cout << "ERROR COMPILATING PROGRAM: " << infoLog << '\n';
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // clang-format off
	float vertices[] = {
		// Denote that always you have to respect the order of the vertices
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

        // clang-format on
        // is called VBO but really is only the ID to call the vertex buffer
        // object
        unsigned int VBO, VAO;

        // i don't understand the VAO at all
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        // we can call it a EBO but is the same as a VBO, only that us will made
        // the difference
        // GL_ELEMENT_ARRAY_BUFFER instead of GL_ARRAY_BUFFER
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
        // GL_STATIC_DRAW);

        // I FINALLY UNDERSTAND, THIS CONVERTS THE DATA OF THE
        // VERTICES INTO THE VEC3 FOR GSLS. VAO only caches this
        // function full explanation ahead. The vao only stores the
        // attributes and how OpenGL should interpret the data of
        // the VBO, so you can generate as much VBO you want,
        // without caring of commanding how opengl with interpret
        // the data as much you indicate in the first VAO.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                              (void *)0);
        glEnableVertexAttribArray(0);

        // i think this is for free memory
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        while (!glfwWindowShouldClose(window)) {
                processInput(window);

                // rendering commands here
                // this sets the color that will be used by
                // `glClear`
                glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
                glClear(GL_COLOR_BUFFER_BIT);

                glUseProgram(shaderProgram);
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
