#ifndef SUNFLOWERSPANIEL_TREE_H
#define SUNFLOWERSPANIEL_TREE_H


#include <Falcon/2D/SpriteBatch/SpriteBatch.h>
#include <Falcon/2D/TileSheet.h>
#include <Box2D/Box2D.h>
#include <Falcon/2D/DebugRenderer/DebugRenderer.h>


class Tree
{
public:
    Tree(b2World* world, glm::vec4 posVec, Falcon::TileSheet& tileSheet, int tileSize)
            : m_position(posVec), m_tileSheet(tileSheet), m_tileSize(tileSize)
    {
    };

    virtual ~Tree() {};
    virtual void drawToSpriteBatch(Falcon::SpriteBatch& spriteBatch) = 0;

protected:
    glm::vec4 m_position;
    Falcon::TileSheet m_tileSheet;
    int m_tileSize = 0;

};


#endif
