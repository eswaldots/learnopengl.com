#ifndef SHADER_H
#define SHADER_H

#include <string>
class Shader {
      public:
        unsigned int ID;
        Shader(const char *vertexPath, const char *fragmentPath);

        void use();

        // uniform functions
        void setBool(const std::string &name, bool value);
        void setInt(const std::string &name, int value);
        void setFloat(const std::string &name, float value);
};

#endif
