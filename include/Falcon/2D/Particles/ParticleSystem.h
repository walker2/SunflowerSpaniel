#ifndef FALCONLATINUM_PARTICLESYSTEM_H
#define FALCONLATINUM_PARTICLESYSTEM_H

#include "../SpriteBatch/SpriteBatch.h"
#include "ParticleBatch.h"

namespace Falcon
{
    class ParticleSystem
    {
    public:
        ParticleSystem();
        ~ParticleSystem();

        void addParticleBatch(ParticleBatch* particleBatch);

        void update(float deltaTime);

        void draw(SpriteBatch* spriteBatch);

    private:
        std::vector<ParticleBatch*> m_batches;
    };
}

#endif