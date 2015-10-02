#include <iostream>
    using std::cout;
    using std::endl;
#include <cassert>

#include "../../inc/engine/state_stack.hpp"

StateStack::StateStack()
    : states()
    , list()
{

}

StateStack::~StateStack()
{

}

void StateStack::HandleEvents(sf::Event _evt)
{
    // Error checking
    assert(!list.empty());
}

void StateStack::Update(sf::Time _elapsed_time)
{
    // Error checking
    assert(!list.empty());

    list.top()->Update(_elapsed_time);
}

void StateStack::Render(sf::RenderWindow& _window)
{
    // Error checking
    assert(!list.empty());

    list.top()->Render(_window);
}

void StateStack::AddState(string _key, shared_ptr<State> _state)
{
    // Error checking
    assert(!_key.empty());
    assert(_state != nullptr);

    states[_key] = _state;
}

void StateStack::RemoveState(string _key)
{
    // Error checking
    assert(!_key.empty());
    assert(states.find(_key) != states.end());

    states.erase(_key);
}

void StateStack::Push(string _key, string _params)
{
    // Error checking
    assert(!_key.empty());
    assert(states.find(_key) != states.end());

    if (list.empty() || list.top() != states[_key])
    {
        list.push(states[_key]);
        list.top()->OnEnter(_params);
    }
}

shared_ptr<State> StateStack::Pop()
{
    if (list.size() == 1)
        return nullptr;

    list.top()->OnExit();
    shared_ptr<State> popped = list.top();
    list.pop();
    return popped;
}