#ifndef FALCONLATINUM_DEBUGRENDERER_H
#define FALCONLATINUM_DEBUGRENDERER_H

#include <glm/glm.hpp>
#include "../Vertex.h"
#include "../../GLSL/ShaderProgram.h"
#include <vector>

namespace Falcon
{
    class DebugRenderer
    {
    public:
        DebugRenderer() {};
        ~DebugRenderer() { dispose(); };

        void init();
        void end();
        void drawBox(const glm::vec4& destRect, const Color& color, float angle);
        void drawCircle(const glm::vec2& center, const Color& color, float radius);
        void render(const glm::mat4& projectionMatrix, float lineWidth);
        void dispose();

        struct DebugVertex
        {
            glm::vec2 position;
            Falcon::Color color;
        };

    private:
        Falcon::ShaderProgram m_shaderProgram;

        std::vector<DebugVertex> m_verts;
        std::vector<GLuint> m_indices;
        GLuint m_vbo = 0, m_vao = 0, m_ibo = 0;

        int m_numElements = 0;

    };
}



#endif
