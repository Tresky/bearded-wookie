#include <iostream>
    using std::cout;
    using std::endl;
#include <cassert>

#include "../../inc/engine/state_machine.hpp"

StateMachine::StateMachine()
    : states()
    , current_state(nullptr)
{

}

StateMachine::~StateMachine()
{

}

void StateMachine::Update(float _elapsed_time)
{
    current_state->Update(_elapsed_time);
}

void StateMachine::Render(sf::RenderWindow& _window)
{
    current_state->Render(_window);
}

void StateMachine::AddState(string _key, shared_ptr<State> _state)
{
    // Error checking
    assert(!_key.empty());
    assert(_state != nullptr);

    states[_key] = _state;
}

void StateMachine::ChangeState(string _key, string _params)
{
    // Error checking
    assert(!_key.empty());
    assert(states.find(_key) != states.end());

    if (current_state)
        current_state->OnExit();
    current_state = states[_key];
    current_state->OnEnter(_params);
}

void StateMachine::RemoveState(string _key)
{
    // Error checking
    assert(!_key.empty());
    assert(states.find(_key) != states.end());

    states.erase(_key);
}