#ifndef SUNFLOWERSPANIEL_OAKTREE_H
#define SUNFLOWERSPANIEL_OAKTREE_H


#include "Tree.h"

class OakTree : public Tree
{
public:
    OakTree(b2World* world, glm::vec4 posVec, Falcon::TileSheet& tileSheet, int tileSize) : Tree(world, posVec, tileSheet, tileSize) {};
    void drawToSpriteBatch(Falcon::SpriteBatch &spriteBatch) override;
};


#endif
