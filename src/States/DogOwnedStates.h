#ifndef SUNFLOWERSPANIEL_DOGOWNEDSTATES_H
#define SUNFLOWERSPANIEL_DOGOWNEDSTATES_H

#include "../FSM/State.h"

class DogAIComponent;

struct Telegram;

class LayDownAndRest : public State<DogAIComponent>
{
public:
    static LayDownAndRest *instance()
    {
        static LayDownAndRest instance;
        return &instance;
    }

    void enter(DogAIComponent *object) override;

    void execute(DogAIComponent *object) override;

    void exit(DogAIComponent *object) override;

    bool onMessage(DogAIComponent *object, const Telegram &telegram) override;


private:
    LayDownAndRest()
    {}

    LayDownAndRest(const LayDownAndRest &);

    LayDownAndRest &operator=(const LayDownAndRest &);
};


class SniffOutThePrey : public State<DogAIComponent>
{
public:
    static SniffOutThePrey *instance()
    {
        static SniffOutThePrey instance;
        return &instance;
    }

    void enter(DogAIComponent *object) override;

    void execute(DogAIComponent *object) override;

    void exit(DogAIComponent *object) override;

    bool onMessage(DogAIComponent *object, const Telegram &telegram) override;


private:
    SniffOutThePrey()
    {}

    SniffOutThePrey(const SniffOutThePrey &);

    SniffOutThePrey &operator=(const SniffOutThePrey &);
};

#endif
