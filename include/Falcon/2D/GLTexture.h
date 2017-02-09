#ifndef FALCONLATINUM_GLTEXTURE_H
#define FALCONLATINUM_GLTEXTURE_H

#include <GL/glew.h>
namespace Falcon
{
    struct GLTexture
    {
        GLuint id;
        int width;
        int height;
    };
}
#endif
