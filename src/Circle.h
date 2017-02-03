#ifndef SUNFLOWERSPANIEL_CIRCLE_H
#define SUNFLOWERSPANIEL_CIRCLE_H

#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include "Falcon/2D/SpriteBatch/SpriteBatch.h"
#include "Falcon/2D/GLTexture.h"
#include "Falcon/2D/DebugRenderer/DebugRenderer.h"
#include "GameObject.h"

class Circle : public GameObject
{
public:
    Circle();
    void destroy()
    {
        auto body = getComponent<BodyComponent>()->getBody();
        if (body) body->GetWorld()->DestroyBody(body);
    };
    void init(b2World* world, const glm::vec2 position, const glm::vec2 dimensions, bool fixedRotation, b2BodyType bodyType);
    void drawDebug(Falcon::DebugRenderer& debugRenderer);
    void update(float deltaTime) override {};

};


#endif
