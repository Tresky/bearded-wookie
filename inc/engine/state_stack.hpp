#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <string>
    using std::string;
#include <map>
    using std::map;
#include <stack>
    using std::stack;
#include <memory>
    using std::shared_ptr;

#include <SFML/Graphics.hpp>

#include "./state.hpp"

// Include all possible state headers for convenience
#include "states/main_menu_state.hpp"
#include "states/local_map_state.hpp"
#include "states/world_map_state.hpp"
#include "states/combat_state.hpp"
#include "states/ingame_menu_state.hpp"

class StateStack
{
public:
    // Default constructor
    StateStack();

    // Default destructor
    ~StateStack();

    /*
     * Handles any events specific to the state.
     *
     * @param[in] _evt Current event object to process
     *
     * @retval none
     */
    void HandleEvents(sf::Event _evt);

    /*
     * Updates the current game state.
     *
     * @param[in] _elapsed_time Current frames elapsed time
     *
     * @retval none
     */
    void Update(sf::Time _elapsed_time);

    /*
     * Renders the current game state.
     *
     * @param[in] _window Window to render to
     *
     * @retval none
     */
    void Render(sf::RenderWindow& _window);

    /*
     * Adds a new game state to the Stack.
     *
     * @param[in] _key String value to refer to the state
     * @param[in] _state State object to store
     *
     * @retval none
     */
    void AddState(string _key, shared_ptr<State> _state);

    /*
     * Removes state with specified key value from the list.
     *
     * @param[in] _key Key of state to remove
     *
     * @retval none
     */
    void RemoveState(string _key);

    /*
     * Push the specified state onto the stack.
     *
     * @param[in] _key Key of state to push
     * @param[in] _params Parameters to pass to the new state
     *
     * @retval none
     */
    void Push(string _key, string _params = "");

    /*
     * Pops the top-most state and returns to the next lowest.
     *
     * @retval Popped state on success
     * @retval nullptr on failure, last state in stack
     */
    shared_ptr<State> Pop();

private:
    // Disabled copy constructor
    StateStack(const StateStack& _copy) = delete;

    // Disabled copy assignment operator
    StateStack& operator=(const StateStack& _copy) = delete;

    // Disabled move contructor
    StateStack(const StateStack&& _moveable) = delete;

    // States for the state stack to use
    map<string, shared_ptr<State>> states;

    // Stack to hold lined up states
    stack<shared_ptr<State>> list;
};

#endif