#ifndef SUNFLOWERSPANIEL_CIRCLE_H
#define SUNFLOWERSPANIEL_CIRCLE_H

#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include "Falcon/2D/SpriteBatch/SpriteBatch.h"
#include "Falcon/2D/GLTexture.h"
#include "Falcon/2D/DebugRenderer/DebugRenderer.h"

class Circle
{
public:
    void init(b2World* world, const glm::vec2 position, const glm::vec2 dimensions, bool fixedRotation);
    void drawDebug(Falcon::DebugRenderer& debugRenderer) const;

    b2Body* getBody() const { return m_body; };
    b2Fixture* getFixture() const { return m_fixture; };
    const glm::vec2& getDimensions() const { return m_dimensions; };

private:
    b2Body* m_body = nullptr;
    b2Fixture* m_fixture = nullptr;
    glm::vec2 m_dimensions;
};


#endif
