#ifndef SUNFLOWERSPANIEL_COLLISIONCOMPONENT_H
#define SUNFLOWERSPANIEL_COLLISIONCOMPONENT_H


#include <Box2D/Box2D.h>
#include <Falcon/2D/DebugRenderer/DebugRenderer.h>
#include "../ObjectFactory/GameObject.h"

class CollisionComponent : public Component
{
public:
    CollisionComponent(GameObject *obj) : Component(obj)
    {}

    virtual void init(tinyxml2::XMLNode *pNode) override;

    void init(GameObject *obj, b2Shape *shape, const glm::vec2 dimensions);

    void update(GameObject *obj, float deltaTime);

    // Maybe this should be another component but this seems logical enough
    void drawDebug(Falcon::DebugRenderer &debugRenderer, Falcon::Color color);


    b2Fixture *getFixture() const
    { return m_fixture; }

    glm::vec2 getDimensions() const
    { return m_dimensions; }

    void setFixture(b2Fixture *fixture)
    { m_fixture = fixture; }

    void setDimensions(glm::vec2 dims)
    { m_dimensions = dims; }

    void setObject(GameObject *obj)
    { m_obj = obj; }


protected:
    GameObject *m_obj;
    b2Fixture *m_fixture;
    b2Body *m_body = nullptr;
    glm::vec2 m_dimensions;
};


#endif
