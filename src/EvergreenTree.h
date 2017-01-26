#ifndef SUNFLOWERSPANIEL_EVERGREENTREE_H
#define SUNFLOWERSPANIEL_EVERGREENTREE_H


#include "Tree.h"

class EvergreenTree : public Tree
{
public:
    EvergreenTree(b2World* world, glm::vec4 posVec, Falcon::TileSheet& tileSheet, int tileSize) : Tree(world, posVec, tileSheet, tileSize) {};
    void drawToSpriteBatch(Falcon::SpriteBatch &spriteBatch) override;
};


#endif
