#ifndef FALCONLATINUM_PARTICLEBATCH_H
#define FALCONLATINUM_PARTICLEBATCH_H

#include <glm/glm.hpp>
#include <functional>
#include "../Vertex.h"
#include "../SpriteBatch/SpriteBatch.h"
#include "../GLTexture.h"

namespace Falcon
{

    class Particle
    {
    public:
        glm::vec2 position = glm::vec2(0.0f);
        glm::vec2 velocity = glm::vec2(0.0f);
        Color color;
        float width = 0.0f; ///< Width of particle
        float life = 0.0f; ///< If zero than particle is inactive
    };

    inline void defaultParticleUpdate(Particle& particle, float deltaTime)
    {
        particle.position += particle.velocity * deltaTime;
    }

    class ParticleBatch
    {
    public:

        ParticleBatch();
        ~ParticleBatch();

        void init(int maxParticles, float decayRate, GLTexture texture, std::function<void(Particle&, float)> updateFunc = defaultParticleUpdate);
        void update(float deltaTime);
        void draw(SpriteBatch* spriteBatch);

        void addParticle(const glm::vec2 position, const glm::vec2 velocity, const Color color, float width);

    private:
        int findFreeParticle();

    private:
        float m_decayRate = 0.1f; ///< Deplete particle life by this amount
        int m_firstFreeParticle; ///< Store first of free particles for quick access
        int m_maxParticles = 0; ///< Sets maximum capacity of m_particles array

        Particle* m_particles = nullptr; ///< Cache friendly container for particles
        GLTexture m_texture; ///< Texture of all particles
        std::function<void(Particle&, float)> m_updateFunc;

    };

}



#endif
