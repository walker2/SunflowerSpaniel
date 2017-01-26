#ifndef SUNFLOWERSPANIEL_TREE_H
#define SUNFLOWERSPANIEL_TREE_H


#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <Falcon/2D/TileSheet.h>
#include "Circle.h"

class Tree
{
public:
    Tree(b2World* world, glm::vec4 posVec, Falcon::TileSheet& tileSheet, int tileSize)
            : m_position(posVec), m_tileSheet(tileSheet), m_tileSize(tileSize)
    {
        m_trunkCollision.init(world, glm::vec2(m_position.x + m_tileSize * 0.5, m_position.y  + m_tileSize * 0.4 ),
                              glm::vec2(m_tileSize * 0.7, m_tileSize * 0.7), true, b2_staticBody);
    };

    virtual ~Tree() {};
    virtual void drawToSpriteBatch(Falcon::SpriteBatch& spriteBatch) = 0;
    void drawDebug(Falcon::DebugRenderer &debugRenderer)
    {
        m_trunkCollision.drawDebug(debugRenderer);
    };

    Circle* getCollision() { return &m_trunkCollision; };

protected:
    Circle m_trunkCollision;
    glm::vec4 m_position;
    Falcon::TileSheet m_tileSheet;
    int m_tileSize = 0;

};


#endif
