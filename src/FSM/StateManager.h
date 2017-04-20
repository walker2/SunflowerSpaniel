#ifndef SUNFLOWERSPANIEL_STATEMANAGER_H
#define SUNFLOWERSPANIEL_STATEMANAGER_H

#include "State.h"
#include "../Messaging/Telegram.h"

template<class game_object>
class StateManager
{
public:
    StateManager(game_object *owner) : m_owner(owner),
                                       m_currentState(NULL),
                                       m_prevState(NULL),
                                       m_globalState(NULL)
    {}

    virtual ~StateManager()
    {}

    /// Use these methods to initialize the FSM
    void setCurrentState(State<game_object> *s)
    { m_currentState = s; }

    void setGlobalState(State<game_object> *s)
    { m_globalState = s; }

    void setPreviousState(State<game_object> *s)
    { m_prevState = s; }

    //call this to update the FSM
    void update() const
    {
        //if a global state exists, call its execute method, else do nothing
        if (m_globalState) m_globalState->execute(m_owner);

        //same for the current state
        if (m_currentState) m_currentState->execute(m_owner);
    }

    bool handleMessage(const Telegram &msg) const
    {
        //first see if the current state is valid and that it can handle
        //the message
        if (m_currentState && m_currentState->onMessage(m_owner, msg))
        {
            return true;
        }

        //if not, and if a global state has been implemented, send
        //the message to the global state
        if (m_globalState && m_globalState->onMessage(m_owner, msg))
        {
            return true;
        }

        return false;
    }

    //change to a new state
    void changeState(State<game_object> *pNewState)
    {
        assert(pNewState && "<StateMachine::ChangeState>:trying to assign null state to current");

        //keep a record of the previous state
        m_prevState = m_currentState;

        //call the exit method of the existing state
        m_currentState->exit(m_owner);

        //change state to the new state
        m_currentState = pNewState;

        //call the entry method of the new state
        m_currentState->enter(m_owner);
    }

    //change state back to the previous state
    void revertToPreviousState()
    {
        changeState(m_prevState);
    }

    /*
    bool isInState(const State<game_object> &st) const
    {
        if (typeid(*m_currentState) == typeid(st)) return true;
        return false;
    }*/

    State<game_object> *currentState() const
    { return m_currentState; }

    State<game_object> *globalState() const
    { return m_globalState; }

    State<game_object> *previousState() const
    { return m_prevState; }

private:
    /// A pointer to the agent that owns this instance
    game_object *m_owner;
    State<game_object> *m_currentState;
    State<game_object> *m_prevState;
    State<game_object> *m_globalState;

};


#endif
