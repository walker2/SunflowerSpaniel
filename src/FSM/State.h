#ifndef SUNFLOWERSPANIEL_STATE_H
#define SUNFLOWERSPANIEL_STATE_H

struct Telegram;

template<class game_object>
class State
{
public:

    virtual ~State()
    {}

    /// This will execute when the state is entered
    virtual void enter(game_object *) = 0;

    /// This is the states normal update function
    virtual void execute(game_object *) = 0;

    /// This will execute when the state is exited.
    virtual void exit(game_object *) = 0;

    /// This executes if the agent receives a message from the message manager
    virtual bool onMessage(game_object *, const Telegram &) = 0;

};


#endif
