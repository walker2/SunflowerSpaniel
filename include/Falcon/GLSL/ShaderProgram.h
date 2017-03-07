#ifndef FALCONLATINUM_GLSLPROGRAM_H
#define FALCONLATINUM_GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>
namespace Falcon
{
    class ShaderProgram
    {
    public:
        ShaderProgram() : m_numAttributes(0), m_programID(0), m_vertShaderID(0), m_fragShaderID(0) {};

        ~ShaderProgram() {};

        void compileShaders(const std::string &vertShaderPath, const std::string &fragShaderPath);

        void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

        void linkShaders();

        void addAttribute(const std::string &attributeName);

        void use();

        void unuse();

        GLint getUniformLocation(const std::string &uniformName);

        void dispose();

    private:
        void compileShader(const char* source, const std::string& name, GLuint id);

    private:
        GLuint m_numAttributes;

        GLuint m_programID;
        GLuint m_vertShaderID;
        GLuint m_fragShaderID;
    };
}

#endif //FALCONLATINUM_GLSLPROGRAM_H
