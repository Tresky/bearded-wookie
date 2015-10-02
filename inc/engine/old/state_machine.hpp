#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <string>
    using std::string;
#include <map>
    using std::map;
#include <memory>
    using std::shared_ptr;

#include <SFML/Graphics.hpp>

#include "./state.hpp"

class StateMachine
{
public:
    // Default constructor
    StateMachine();

    // Default destructor
    ~StateMachine();

    /*
     * Updates the current game state.
     *
     * @param[in] _elapsed_time Current frames elapsed time
     *
     * @retval none
     */
    void Update(float _elapsed_time);

    /*
     * Renders the current game state.
     *
     * @param[in] _window Window to render to
     *
     * @retval none
     */
    void Render(sf::RenderWindow& _window);

    /*
     * Adds a new game state to the machine.
     *
     * @param[in] _key String value to refer to the state
     * @param[in] _state State object to store
     *
     * @retval none
     */
    void AddState(string _key, shared_ptr<State> _state);

    /*
     * Changes the current state.
     *
     * @param[in] _key Key of the state to change to
     * @param[in] _params Parameters to pass into new state (JSON)
     *
     * @retval none
     */
    void ChangeState(string _key, string _params = "");

    /*
     * Removes state with specified key value from the list.
     *
     * @param[in] _key Key of state to remove
     *
     * @retval none
     */
    void RemoveState(string _key);

private:
    // Disabled copy constructor
    StateMachine(const StateMachine& _copy) = delete;

    // Disabled copy assignment operator
    StateMachine& operator=(const StateMachine& _copy) = delete;

    // Disabled move contructor
    StateMachine(const StateMachine&& _moveable) = delete;

    // States for the state machine to use
    map<string, shared_ptr<State>> states;

    // Current state of the machine
    shared_ptr<State> current_state;
};

#endif