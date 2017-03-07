#ifndef FALCONLATINUM_SPRITEBATCH_H
#define FALCONLATINUM_SPRITEBATCH_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <vector>
#include "../Vertex.h"
#include <GL/glew.h>

enum class GlyphSortType
{
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

namespace Falcon
{

    class Glyph
    {
    public:
        Glyph() {};
        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const Color &color);
        Glyph(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint Texture, float Depth, const Color &color, float angle);

        GLuint texture;
        float depth;
        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;

    private:
        glm::vec2 rotatePoint(glm::vec2 position, float angle);
    };

    class RenderBatch
    {
    public:
        RenderBatch(GLuint _offset, GLuint _num, GLuint _texture) : offset(_offset), numVertices(_num), texture(_texture) {};
        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };

    class SpriteBatch
    {
    public:
        SpriteBatch() :
           m_vbo(0),
	   m_vao(0)
        {}

        void init();

        void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
        void end();

        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color);
        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color, float angle);
        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color, const glm::vec2 dir);
        void renderBatch();

    private:
        void createRenderBatches();
        void createVertexArray();
        void sortGlyphs();

        static bool cmpFTB(Glyph* a, Glyph* b);
        static bool cmpBTF(Glyph* a, Glyph* b);
        static bool cmpTXT(Glyph* a, Glyph* b);
    private:
        GlyphSortType m_sortType;
        GLuint m_vbo; // Vertex buffer object
        GLuint m_vao; // Vertex array object

        std::vector<Glyph*> m_glyphPtrs; // Vector for sorting
        std::vector<Glyph> m_glyphs;
        std::vector<RenderBatch> m_renderBatches;
    };
}




#endif
