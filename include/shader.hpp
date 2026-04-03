#ifndef SHADER_H
#define SHADER_H

#include <cstdio>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
      public:
        unsigned int ID;
        Shader(const char *vertexPath, const char *fragmentPath) {
                std::string vertexCode;
                std::string fragmentCode;

                std::ifstream vShaderFile;
                std::ifstream fShaderFile;

                vShaderFile.exceptions(std::ifstream::failbit |
                                       std::ifstream::badbit);

                fShaderFile.exceptions(std::ifstream::failbit |
                                       std::ifstream::badbit);

                try {
                        vShaderFile.open(vertexPath);
                        fShaderFile.open(fragmentPath);

                        std::stringstream vStream, fStream;

                        vStream << vShaderFile.rdbuf();
                        fStream << fShaderFile.rdbuf();

                        vShaderFile.close();
                        fShaderFile.close();

                        vertexCode = vStream.str();
                        fragmentCode = fStream.str();
                } catch (std::ifstream::failure e) {
                        std::cout << "ERROR: error reading shader files\n";
                }

                const char *vShaderCode = vertexCode.c_str();
                const char *fShaderCode = fragmentCode.c_str();

                std::cout
                    << "DEBUG: vShaderCode and fShaderCode initialized \n";

                unsigned int vID = glCreateShader(GL_VERTEX_SHADER);

                std::cout << "DEBUG: vShader created\n";

                // TODO: why null?
                glShaderSource(vID, 1, &vShaderCode, NULL);

                std::cout << "DEBUG: vShaderCode source attached\n";

                glCompileShader(vID);

                int success;
                char infoLog[256];

                glGetShaderiv(vID, GL_COMPILE_STATUS, &success);

                if (!success) {
                        glGetShaderInfoLog(vID, 256, NULL, infoLog);

                        std::cout << "ERROR COMPILATING SHADER: " << infoLog
                                  << '\n';
                }

                unsigned int fID = glCreateShader(GL_FRAGMENT_SHADER);

                // TODO: why null?
                glShaderSource(fID, 1, &fShaderCode, NULL);

                glCompileShader(fID);

                glGetShaderiv(fID, GL_COMPILE_STATUS, &success);

                if (!success) {
                        glGetShaderInfoLog(fID, 256, NULL, infoLog);

                        std::cout << "ERROR COMPILATING SHADER: " << infoLog
                                  << '\n';
                }

                ID = glCreateProgram();

                glAttachShader(ID, vID);
                glAttachShader(ID, fID);

                glLinkProgram(ID);

                glGetProgramiv(ID, GL_LINK_STATUS, &success);

                if (!success) {
                        glGetProgramInfoLog(ID, 256, NULL, infoLog);

                        std::cout << "ERROR COMPILATING PROGRAM: " << infoLog
                                  << '\n';
                }

                glDeleteShader(vID);
                glDeleteShader(fID);
        };

        void use() { glUseProgram(ID); };

        // uniform functions
        void setBool(const std::string &name, bool value) {
                glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        };
        void setInt(const std::string &name, int value) {
                glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        };
        void setFloat(const std::string &name, float value) {
                glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        };
};

#endif
