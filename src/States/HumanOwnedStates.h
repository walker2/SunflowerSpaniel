#ifndef SUNFLOWERSPANIEL_HUMANOWNEDSTATES_H
#define SUNFLOWERSPANIEL_HUMANOWNEDSTATES_H

#include "../FSM/State.h"

class HumanAIComponent;

struct Telegram;

class Sleep : public State<HumanAIComponent>
{
public:
    static Sleep *instance()
    {
        static Sleep instance;
        return &instance;
    }

    void enter(HumanAIComponent *object) override;

    void execute(HumanAIComponent *object) override;

    void exit(HumanAIComponent *object) override;

    bool onMessage(HumanAIComponent *object, const Telegram &telegram) override;


private:
    Sleep()
    {}

    Sleep(const Sleep &);

    Sleep &operator=(const Sleep &);
};


class Hunt : public State<HumanAIComponent>
{
public:
    static Hunt *instance()
    {
        static Hunt instance;
        return &instance;
    }

    void enter(HumanAIComponent *object) override;

    void execute(HumanAIComponent *object) override;

    void exit(HumanAIComponent *object) override;

    bool onMessage(HumanAIComponent *object, const Telegram &telegram) override;


private:
    Hunt()
    {}

    Hunt(const Hunt &);

    Hunt &operator=(const Hunt &);
};


#endif
