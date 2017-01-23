#ifndef SUNFLOWERSPANIEL_BOX_H
#define SUNFLOWERSPANIEL_BOX_H


#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include "Falcon/2D/SpriteBatch/SpriteBatch.h"
#include "Falcon/2D/GLTexture.h"
#include "Falcon/2D/DebugRenderer/DebugRenderer.h"

class Box
{
public:
    Box();
    ~Box();

    void init(b2World* world, const glm::vec2 position, const glm::vec2 dimensions, Falcon::GLTexture texture,
              bool fixedRotation, glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

    void draw(Falcon::SpriteBatch& spriteBatch);
    void drawDebug(Falcon::DebugRenderer& debugRenderer) const;


    b2Body* getBody() const { return m_body; };
    b2Fixture* getFixture() const { return m_fixture; };
    const glm::vec2& getDimensions() const { return m_dimensions; };


private:
    b2Body* m_body = nullptr;
    b2Fixture* m_fixture = nullptr;
    glm::vec2 m_dimensions;
    glm::vec4 m_uvRect;
    Falcon::GLTexture m_texture;

};


#endif
