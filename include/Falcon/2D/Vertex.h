#ifndef FALCONLATINUM_VERTEX_H
#define FALCONLATINUM_VERTEX_H

#include <GL/glew.h>
namespace Falcon
{
    struct Position
    {
        float x;
        float y;
    };

    struct Color
    {
        Color(){};
        Color(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) : r(_r), g(_g), b(_b), a(_a) {};

        Color operator-(const Color& c)
        {
            Color color(r - c.r, g - c.g, b - c.b, a - c.a);
            return color;
        };
        void setColor(GLubyte _r, GLubyte _g, GLubyte _b,  GLubyte _a = 255)
        {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }

        GLubyte r = 0;
        GLubyte g = 0;
        GLubyte b = 0;
        GLubyte a = 255;
    };

    struct UV {
        float u;
        float v;
    };


    struct Vertex
    {

        Position position;
        Color color;
        UV uv;

        void setPosition(float x, float y)
        {
            position.x = x;
            position.y = y;
        }

        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
        {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }

        void setUV(float u, float v)
        {
            uv.u = u;
            uv.v = v;
        }

    };
}

#endif //FALCONLATINUM_VERTEX_H
