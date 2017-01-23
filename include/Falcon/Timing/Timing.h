#ifndef FALCONLATINUM_TIMING_H
#define FALCONLATINUM_TIMING_H

namespace Falcon
{
    class FPSLimiter
    {
    public:
        FPSLimiter() {};
        void init(float targetFPS);

        void setTargetFPS(float targetFPS);

        void begin();

        float end(); // Returns current fps
    private:
        void calculateFPS();
    private:
        unsigned int m_startTicks;

        float m_targetFPS;
        float m_FPS;
        float m_frameTime;
        float m_maxFPS;
    };
}


#endif
